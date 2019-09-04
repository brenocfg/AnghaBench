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

/* Variables and functions */
 struct bstr bstr_splitchar (struct bstr,struct bstr*,char) ; 

__attribute__((used)) static inline struct bstr bstr_getline(struct bstr str, struct bstr *rest)
{
    return bstr_splitchar(str, rest, '\n');
}