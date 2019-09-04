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
 int /*<<< orphan*/  bstr0 (char const*) ; 
 int bstr_endswith (struct bstr,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool bstr_endswith0(struct bstr str, const char *suffix)
{
    return bstr_endswith(str, bstr0(suffix));
}