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
typedef  int /*<<< orphan*/  uint8_t ;
struct hvsi_header {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ VS_QUERY_RESPONSE_PACKET_HEADER ; 

__attribute__((used)) static inline int is_header(const uint8_t *packet)
{
	struct hvsi_header *header = (struct hvsi_header *)packet;
	return header->type >= VS_QUERY_RESPONSE_PACKET_HEADER;
}