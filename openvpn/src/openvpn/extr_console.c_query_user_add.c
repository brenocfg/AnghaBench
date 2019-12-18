#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* prompt; size_t prompt_len; char* response; size_t response_len; int echo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int QUERY_USER_NUMSLOTS ; 
 TYPE_1__* query_user ; 

void
query_user_add(char *prompt, size_t prompt_len,
               char *resp, size_t resp_len,
               bool echo)
{
    int i;

    /* Ensure input is sane.  All these must be present otherwise it is
     * a programming error.
     */
    ASSERT( prompt_len > 0 && prompt != NULL && resp_len > 0 && resp != NULL );

    /* Seek to the last unused slot */
    for (i = 0; i < QUERY_USER_NUMSLOTS; i++)
    {
        if (query_user[i].prompt == NULL)
        {
            break;
        }
    }
    ASSERT( i < QUERY_USER_NUMSLOTS );  /* Unlikely, but we want to panic if it happens */

    /* Save the information needed for the user interaction */
    query_user[i].prompt = prompt;
    query_user[i].prompt_len = prompt_len;
    query_user[i].response = resp;
    query_user[i].response_len = resp_len;
    query_user[i].echo = echo;
}