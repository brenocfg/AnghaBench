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
struct bstr {scalar_t__ len; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline bool bstr_endswith(struct bstr str, struct bstr suffix)
{
    if (str.len < suffix.len)
        return false;
    return !memcmp(str.start + str.len - suffix.len, suffix.start, suffix.len);
}