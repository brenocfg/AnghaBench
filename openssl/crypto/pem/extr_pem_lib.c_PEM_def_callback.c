#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char* EVP_get_pw_prompt () ; 
 int EVP_read_pw_string_min (char*,int,int,char const*,int) ; 
 int MIN_LENGTH ; 
 int /*<<< orphan*/  PEM_F_PEM_DEF_CALLBACK ; 
 int /*<<< orphan*/  PEM_R_PROBLEMS_GETTING_PASSWORD ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int strlen (char*) ; 

int PEM_def_callback(char *buf, int num, int rwflag, void *userdata)
{
    int i, min_len;
    const char *prompt;

    /* We assume that the user passes a default password as userdata */
    if (userdata) {
        i = strlen(userdata);
        i = (i > num) ? num : i;
        memcpy(buf, userdata, i);
        return i;
    }

    prompt = EVP_get_pw_prompt();
    if (prompt == NULL)
        prompt = "Enter PEM pass phrase:";

    /*
     * rwflag == 0 means decryption
     * rwflag == 1 means encryption
     *
     * We assume that for encryption, we want a minimum length, while for
     * decryption, we cannot know any minimum length, so we assume zero.
     */
    min_len = rwflag ? MIN_LENGTH : 0;

    i = EVP_read_pw_string_min(buf, min_len, num, prompt, rwflag);
    if (i != 0) {
        PEMerr(PEM_F_PEM_DEF_CALLBACK, PEM_R_PROBLEMS_GETTING_PASSWORD);
        memset(buf, 0, (unsigned int)num);
        return -1;
    }
    return strlen(buf);
}