#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prompt3 ;
typedef  int /*<<< orphan*/  prompt2 ;
typedef  int /*<<< orphan*/  prompt1 ;
struct TYPE_6__ {TYPE_1__* meth; } ;
typedef  TYPE_2__ UI ;
struct TYPE_5__ {char* (* ui_construct_prompt ) (TYPE_2__*,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  UI_F_UI_CONSTRUCT_PROMPT ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 char* stub1 (TYPE_2__*,char const*,char const*) ; 

char *UI_construct_prompt(UI *ui, const char *object_desc,
                          const char *object_name)
{
    char *prompt = NULL;

    if (ui->meth->ui_construct_prompt != NULL)
        prompt = ui->meth->ui_construct_prompt(ui, object_desc, object_name);
    else {
        char prompt1[] = "Enter ";
        char prompt2[] = " for ";
        char prompt3[] = ":";
        int len = 0;

        if (object_desc == NULL)
            return NULL;
        len = sizeof(prompt1) - 1 + strlen(object_desc);
        if (object_name != NULL)
            len += sizeof(prompt2) - 1 + strlen(object_name);
        len += sizeof(prompt3) - 1;

        if ((prompt = OPENSSL_malloc(len + 1)) == NULL) {
            UIerr(UI_F_UI_CONSTRUCT_PROMPT, ERR_R_MALLOC_FAILURE);
            return NULL;
        }
        OPENSSL_strlcpy(prompt, prompt1, len + 1);
        OPENSSL_strlcat(prompt, object_desc, len + 1);
        if (object_name != NULL) {
            OPENSSL_strlcat(prompt, prompt2, len + 1);
            OPENSSL_strlcat(prompt, object_name, len + 1);
        }
        OPENSSL_strlcat(prompt, prompt3, len + 1);
    }
    return prompt;
}