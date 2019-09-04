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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/ * d8; int /*<<< orphan*/  d32; } ;
struct TYPE_5__ {int position; TYPE_1__ part; } ;
typedef  TYPE_2__ emmh32_context ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_ACCUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emmh32_update(emmh32_context *context, u8 *pOctets, int len)
{
	int	coeff_position, byte_position;
  
	if (len == 0) return;
  
	coeff_position = context->position >> 2;
  
	/* deal with partial 32-bit word left over from last update */
	byte_position = context->position & 3;
	if (byte_position) {
		/* have a partial word in part to deal with */
		do {
			if (len == 0) return;
			context->part.d8[byte_position++] = *pOctets++;
			context->position++;
			len--;
		} while (byte_position < 4);
		MIC_ACCUM(ntohl(context->part.d32));
	}

	/* deal with full 32-bit words */
	while (len >= 4) {
		MIC_ACCUM(ntohl(*(__be32 *)pOctets));
		context->position += 4;
		pOctets += 4;
		len -= 4;
	}

	/* deal with partial 32-bit word that will be left over from this update */
	byte_position = 0;
	while (len > 0) {
		context->part.d8[byte_position++] = *pOctets++;
		context->position++;
		len--;
	}
}