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
struct arm_spe_pkt {int dummy; } ;

/* Variables and functions */
 int ARM_SPE_BAD_PACKET ; 
 int ARM_SPE_NEED_MORE_BYTES ; 
 unsigned int SPE_HEADER0_ADDRESS ; 
 unsigned int SPE_HEADER0_ADDRESS_MASK ; 
 unsigned int SPE_HEADER0_CONTEXT ; 
 unsigned int SPE_HEADER0_CONTEXT_MASK ; 
 unsigned int SPE_HEADER0_COUNTER ; 
 unsigned int SPE_HEADER0_COUNTER_MASK ; 
 unsigned int SPE_HEADER0_END ; 
 unsigned int SPE_HEADER0_EVENTS ; 
 unsigned int SPE_HEADER0_EVENTS_MASK ; 
 unsigned int SPE_HEADER0_OP_TYPE ; 
 unsigned int SPE_HEADER0_OP_TYPE_MASK ; 
 unsigned int SPE_HEADER0_PAD ; 
 unsigned int SPE_HEADER0_SOURCE ; 
 unsigned int SPE_HEADER0_SOURCE_MASK ; 
 unsigned int SPE_HEADER0_TIMESTAMP ; 
 unsigned int SPE_HEADER1_ADDRESS ; 
 unsigned int SPE_HEADER1_ADDRESS_MASK ; 
 unsigned int SPE_HEADER1_ALIGNMENT ; 
 unsigned int SPE_HEADER1_COUNTER ; 
 unsigned int SPE_HEADER1_COUNTER_MASK ; 
 int arm_spe_get_addr (unsigned char const*,size_t,int,struct arm_spe_pkt*) ; 
 int arm_spe_get_alignment (unsigned char const*,size_t,struct arm_spe_pkt*) ; 
 int arm_spe_get_context (unsigned char const*,size_t,struct arm_spe_pkt*) ; 
 int arm_spe_get_counter (unsigned char const*,size_t,int,struct arm_spe_pkt*) ; 
 int arm_spe_get_data_source (unsigned char const*,size_t,struct arm_spe_pkt*) ; 
 int arm_spe_get_end (struct arm_spe_pkt*) ; 
 int arm_spe_get_events (unsigned char const*,size_t,struct arm_spe_pkt*) ; 
 int arm_spe_get_op_type (unsigned char const*,size_t,struct arm_spe_pkt*) ; 
 int arm_spe_get_pad (struct arm_spe_pkt*) ; 
 int arm_spe_get_timestamp (unsigned char const*,size_t,struct arm_spe_pkt*) ; 
 int /*<<< orphan*/  memset (struct arm_spe_pkt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arm_spe_do_get_packet(const unsigned char *buf, size_t len,
				 struct arm_spe_pkt *packet)
{
	unsigned int byte;

	memset(packet, 0, sizeof(struct arm_spe_pkt));

	if (!len)
		return ARM_SPE_NEED_MORE_BYTES;

	byte = buf[0];
	if (byte == SPE_HEADER0_PAD)
		return arm_spe_get_pad(packet);
	else if (byte == SPE_HEADER0_END) /* no timestamp at end of record */
		return arm_spe_get_end(packet);
	else if (byte & 0xc0 /* 0y11xxxxxx */) {
		if (byte & 0x80) {
			if ((byte & SPE_HEADER0_ADDRESS_MASK) == SPE_HEADER0_ADDRESS)
				return arm_spe_get_addr(buf, len, 0, packet);
			if ((byte & SPE_HEADER0_COUNTER_MASK) == SPE_HEADER0_COUNTER)
				return arm_spe_get_counter(buf, len, 0, packet);
		} else
			if (byte == SPE_HEADER0_TIMESTAMP)
				return arm_spe_get_timestamp(buf, len, packet);
			else if ((byte & SPE_HEADER0_EVENTS_MASK) == SPE_HEADER0_EVENTS)
				return arm_spe_get_events(buf, len, packet);
			else if ((byte & SPE_HEADER0_SOURCE_MASK) == SPE_HEADER0_SOURCE)
				return arm_spe_get_data_source(buf, len, packet);
			else if ((byte & SPE_HEADER0_CONTEXT_MASK) == SPE_HEADER0_CONTEXT)
				return arm_spe_get_context(buf, len, packet);
			else if ((byte & SPE_HEADER0_OP_TYPE_MASK) == SPE_HEADER0_OP_TYPE)
				return arm_spe_get_op_type(buf, len, packet);
	} else if ((byte & 0xe0) == 0x20 /* 0y001xxxxx */) {
		/* 16-bit header */
		byte = buf[1];
		if (byte == SPE_HEADER1_ALIGNMENT)
			return arm_spe_get_alignment(buf, len, packet);
		else if ((byte & SPE_HEADER1_ADDRESS_MASK) == SPE_HEADER1_ADDRESS)
			return arm_spe_get_addr(buf, len, 1, packet);
		else if ((byte & SPE_HEADER1_COUNTER_MASK) == SPE_HEADER1_COUNTER)
			return arm_spe_get_counter(buf, len, 1, packet);
	}

	return ARM_SPE_BAD_PACKET;
}