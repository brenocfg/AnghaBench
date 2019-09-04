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
typedef  size_t uint32_t ;
struct packet_info {int field_count; struct packet_field* fields; } ;
struct packet_field {int flags; size_t offset; char** value_names; int width; char* name; } ;
struct TYPE_2__ {size_t tcode; } ;
struct link_packet {TYPE_1__ common; } ;

/* Variables and functions */
 int PACKET_FIELD_DATA_LENGTH ; 
 int /*<<< orphan*/  dump_data (unsigned char*,int) ; 
 unsigned long long get_bits (struct link_packet*,int,int) ; 
 struct packet_info* packet_info ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
decode_link_packet(struct link_packet *packet, size_t length,
		   int include_flags, int exclude_flags)
{
	const struct packet_info *pi;
	int data_length = 0;
	int i;

	pi = &packet_info[packet->common.tcode];

	for (i = 0; i < pi->field_count; i++) {
		const struct packet_field *f = &pi->fields[i];
		int offset;

		if (f->flags & exclude_flags)
			continue;
		if (include_flags && !(f->flags & include_flags))
			continue;

		if (f->offset < 0)
			offset = length * 8 + f->offset - 32;
		else
			offset = f->offset;

		if (f->value_names != NULL) {
			uint32_t bits;

			bits = get_bits(packet, offset, f->width);
			printf("%s", f->value_names[bits]);
		} else if (f->width == 0) {
			printf("%s=[", f->name);
			dump_data((unsigned char *) packet + (offset / 8 + 4), data_length);
			printf("]");
		} else {
			unsigned long long bits;
			int high_width, low_width;

			if ((offset & ~31) != ((offset + f->width - 1) & ~31)) {
				/* Bit field spans quadlet boundary. */
				high_width = ((offset + 31) & ~31) - offset;
				low_width = f->width - high_width;

				bits = get_bits(packet, offset, high_width);
				bits = (bits << low_width) |
					get_bits(packet, offset + high_width, low_width);
			} else {
				bits = get_bits(packet, offset, f->width);
			}

			printf("%s=0x%0*llx", f->name, (f->width + 3) / 4, bits);

			if (f->flags & PACKET_FIELD_DATA_LENGTH)
				data_length = bits;
		}

		if (i < pi->field_count - 1)
			printf(", ");
	}
}