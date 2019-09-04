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
struct dlm_header {int /*<<< orphan*/  h_length; void* h_nodeid; void* h_lockspace; void* h_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (void*) ; 

__attribute__((used)) static void header_out(struct dlm_header *hd)
{
	hd->h_version		= cpu_to_le32(hd->h_version);
	hd->h_lockspace		= cpu_to_le32(hd->h_lockspace);
	hd->h_nodeid		= cpu_to_le32(hd->h_nodeid);
	hd->h_length		= cpu_to_le16(hd->h_length);
}