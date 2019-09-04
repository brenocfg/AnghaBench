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
typedef  int /*<<< orphan*/  u32 ;
struct uhci_td {void* buffer; void* token; void* status; } ;
struct uhci_hcd {int dummy; } ;

/* Variables and functions */
 void* cpu_to_hc32 (struct uhci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uhci_fill_td(struct uhci_hcd *uhci, struct uhci_td *td,
		u32 status, u32 token, u32 buffer)
{
	td->status = cpu_to_hc32(uhci, status);
	td->token = cpu_to_hc32(uhci, token);
	td->buffer = cpu_to_hc32(uhci, buffer);
}