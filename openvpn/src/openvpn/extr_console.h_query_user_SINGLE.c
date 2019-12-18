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
 int /*<<< orphan*/  query_user_add (char*,size_t,char*,size_t,int) ; 
 int /*<<< orphan*/  query_user_clear () ; 
 int query_user_exec () ; 

__attribute__((used)) static inline bool
query_user_SINGLE(char *prompt, size_t prompt_len,
                  char *resp, size_t resp_len,
                  bool echo)
{
    query_user_clear();
    query_user_add(prompt, prompt_len, resp, resp_len, echo);
    return query_user_exec();
}