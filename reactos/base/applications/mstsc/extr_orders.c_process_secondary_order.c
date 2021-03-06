#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  scalar_t__ uint16 ;
typedef  int sint16 ;
struct TYPE_11__ {int* p; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
#define  RDP_ORDER_BMPCACHE 134 
#define  RDP_ORDER_BMPCACHE2 133 
#define  RDP_ORDER_BRUSHCACHE 132 
#define  RDP_ORDER_COLCACHE 131 
#define  RDP_ORDER_FONTCACHE 130 
#define  RDP_ORDER_RAW_BMPCACHE 129 
#define  RDP_ORDER_RAW_BMPCACHE2 128 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  in_uint16_le (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  process_bmpcache (TYPE_1__*) ; 
 int /*<<< orphan*/  process_bmpcache2 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_brushcache (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  process_colcache (TYPE_1__*) ; 
 int /*<<< orphan*/  process_fontcache (TYPE_1__*) ; 
 int /*<<< orphan*/  process_raw_bmpcache (TYPE_1__*) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static void
process_secondary_order(STREAM s)
{
	/* The length isn't calculated correctly by the server.
	 * For very compact orders the length becomes negative
	 * so a signed integer must be used. */
	uint16 length;
	uint16 flags;
	uint8 type;
	uint8 *next_order;

	in_uint16_le(s, length);
	in_uint16_le(s, flags);	/* used by bmpcache2 */
	in_uint8(s, type);

	next_order = s->p + (sint16) length + 7;

	switch (type)
	{
		case RDP_ORDER_RAW_BMPCACHE:
			process_raw_bmpcache(s);
			break;

		case RDP_ORDER_COLCACHE:
			process_colcache(s);
			break;

		case RDP_ORDER_BMPCACHE:
			process_bmpcache(s);
			break;

		case RDP_ORDER_FONTCACHE:
			process_fontcache(s);
			break;

		case RDP_ORDER_RAW_BMPCACHE2:
			process_bmpcache2(s, flags, False);	/* uncompressed */
			break;

		case RDP_ORDER_BMPCACHE2:
			process_bmpcache2(s, flags, True);	/* compressed */
			break;

		case RDP_ORDER_BRUSHCACHE:
			process_brushcache(s, flags);
			break;

		default:
			unimpl("secondary order %d\n", type);
	}

	s->p = next_order;
}