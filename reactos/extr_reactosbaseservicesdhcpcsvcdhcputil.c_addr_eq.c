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
struct iaddr {scalar_t__ len; int /*<<< orphan*/  iabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int addr_eq( struct iaddr a, struct iaddr b ) {
    return a.len == b.len && !memcmp( a.iabuf, b.iabuf, a.len );
}