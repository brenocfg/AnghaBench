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
struct afs_call {int /*<<< orphan*/  tmp64; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_extract_begin (struct afs_call*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void afs_extract_to_tmp64(struct afs_call *call)
{
	afs_extract_begin(call, &call->tmp64, sizeof(call->tmp64));
}