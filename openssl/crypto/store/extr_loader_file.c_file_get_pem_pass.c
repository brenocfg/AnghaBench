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
struct pem_pass_data {int /*<<< orphan*/  data; int /*<<< orphan*/  prompt_info; int /*<<< orphan*/  ui_method; } ;

/* Variables and functions */
 char* file_get_pass (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int file_get_pem_pass(char *buf, int num, int w, void *data)
{
    struct pem_pass_data *pass_data = data;
    char *pass = file_get_pass(pass_data->ui_method, buf, num,
                               pass_data->prompt_info, pass_data->data);

    return pass == NULL ? 0 : strlen(pass);
}