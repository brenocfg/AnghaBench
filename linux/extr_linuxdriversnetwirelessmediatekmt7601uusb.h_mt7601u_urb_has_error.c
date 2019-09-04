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
struct urb {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESHUTDOWN ; 

__attribute__((used)) static inline bool mt7601u_urb_has_error(struct urb *urb)
{
	return urb->status &&
		urb->status != -ENOENT &&
		urb->status != -ECONNRESET &&
		urb->status != -ESHUTDOWN;
}