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
struct TYPE_2__ {scalar_t__ magic; } ;
typedef  TYPE_1__ xbe_header ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;

/* Variables and functions */
 scalar_t__ XBE_MAGIC ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 size) {
	xbe_header *header = (xbe_header *) buf;
	return (size > sizeof (xbe_header) && header->magic == XBE_MAGIC);
}