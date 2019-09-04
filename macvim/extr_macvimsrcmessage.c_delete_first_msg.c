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
struct msg_hist {struct msg_hist* msg; struct msg_hist* next; } ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 struct msg_hist* first_msg_hist ; 
 int /*<<< orphan*/ * last_msg_hist ; 
 scalar_t__ msg_hist_len ; 
 int /*<<< orphan*/  vim_free (struct msg_hist*) ; 

int
delete_first_msg()
{
    struct msg_hist *p;

    if (msg_hist_len <= 0)
	return FAIL;
    p = first_msg_hist;
    first_msg_hist = p->next;
    if (first_msg_hist == NULL)
	last_msg_hist = NULL;  /* history is empty */
    vim_free(p->msg);
    vim_free(p);
    --msg_hist_len;
    return OK;
}