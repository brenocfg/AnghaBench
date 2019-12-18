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
struct buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ BLAST (struct buffer*) ; 
 int CC_CRLF ; 
 int CC_NULL ; 
 int /*<<< orphan*/  buf_inc_len (struct buffer*,int) ; 
 int /*<<< orphan*/  buf_null_terminate (struct buffer*) ; 
 scalar_t__ char_class (char,int) ; 

void
buf_chomp(struct buffer *buf)
{
    while (true)
    {
        char *last = (char *) BLAST(buf);
        if (!last)
        {
            break;
        }
        if (char_class(*last, CC_CRLF|CC_NULL))
        {
            if (!buf_inc_len(buf, -1))
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    buf_null_terminate(buf);
}