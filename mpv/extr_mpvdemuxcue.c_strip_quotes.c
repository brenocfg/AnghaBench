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
struct bstr {int dummy; } ;
typedef  struct bstr bstr ;

/* Variables and functions */
 scalar_t__ bstr_eatend0 (struct bstr*,char*) ; 
 scalar_t__ bstr_eatstart0 (struct bstr*,char*) ; 

__attribute__((used)) static struct bstr strip_quotes(struct bstr data)
{
    bstr s = data;
    if (bstr_eatstart0(&s, "\"") && bstr_eatend0(&s, "\""))
        return s;
    return data;
}