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
struct bstr {int len; int start; } ;

/* Variables and functions */
 int MPMAX (int,int) ; 
 int MPMIN (int,int) ; 

struct bstr bstr_splice(struct bstr str, int start, int end)
{
    if (start < 0)
        start += str.len;
    if (end < 0)
        end += str.len;
    end = MPMIN(end, str.len);
    start = MPMAX(start, 0);
    end = MPMAX(end, start);
    str.start += start;
    str.len = end - start;
    return str;
}