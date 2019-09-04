#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* connector; } ;
struct audit_chunk {TYPE_2__ mark; } ;
struct TYPE_3__ {scalar_t__ obj; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static unsigned long chunk_to_key(struct audit_chunk *chunk)
{
	/*
	 * We have a reference to the mark so it should be attached to a
	 * connector.
	 */
	if (WARN_ON_ONCE(!chunk->mark.connector))
		return 0;
	return (unsigned long)chunk->mark.connector->obj;
}