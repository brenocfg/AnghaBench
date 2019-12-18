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
struct afs_call {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_extract_begin (struct afs_call*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void afs_extract_to_buf(struct afs_call *call, size_t size)
{
	afs_extract_begin(call, call->buffer, size);
}