#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {scalar_t__ length; } ;
typedef  TYPE_1__ radius_packet ;
struct TYPE_5__ {int length; int /*<<< orphan*/  data; int /*<<< orphan*/  attribute; } ;
typedef  TYPE_2__ radius_attribute ;

/* Variables and functions */
 scalar_t__ RADIUS_BUFFER_SIZE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static void
radius_add_attribute(radius_packet *packet, uint8 type, const unsigned char *data, int len)
{
	radius_attribute *attr;

	if (packet->length + len > RADIUS_BUFFER_SIZE)
	{
		/*
		 * With remotely realistic data, this can never happen. But catch it
		 * just to make sure we don't overrun a buffer. We'll just skip adding
		 * the broken attribute, which will in the end cause authentication to
		 * fail.
		 */
		elog(WARNING,
			 "adding attribute code %d with length %d to radius packet would create oversize packet, ignoring",
			 type, len);
		return;
	}

	attr = (radius_attribute *) ((unsigned char *) packet + packet->length);
	attr->attribute = type;
	attr->length = len + 2;		/* total size includes type and length */
	memcpy(attr->data, data, len);
	packet->length += attr->length;
}