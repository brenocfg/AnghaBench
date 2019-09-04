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
typedef  enum xhci_ring_type { ____Placeholder_xhci_ring_type } xhci_ring_type ;

/* Variables and functions */
#define  TYPE_BULK 134 
#define  TYPE_COMMAND 133 
#define  TYPE_CTRL 132 
#define  TYPE_EVENT 131 
#define  TYPE_INTR 130 
#define  TYPE_ISOC 129 
#define  TYPE_STREAM 128 

__attribute__((used)) static inline const char *xhci_ring_type_string(enum xhci_ring_type type)
{
	switch (type) {
	case TYPE_CTRL:
		return "CTRL";
	case TYPE_ISOC:
		return "ISOC";
	case TYPE_BULK:
		return "BULK";
	case TYPE_INTR:
		return "INTR";
	case TYPE_STREAM:
		return "STREAM";
	case TYPE_COMMAND:
		return "CMD";
	case TYPE_EVENT:
		return "EVENT";
	}

	return "UNKNOWN";
}