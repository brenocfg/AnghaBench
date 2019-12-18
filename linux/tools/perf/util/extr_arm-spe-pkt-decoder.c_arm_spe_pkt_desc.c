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
struct arm_spe_pkt {int index; unsigned long long payload; int type; } ;

/* Variables and functions */
#define  ARM_SPE_ADDRESS 137 
#define  ARM_SPE_BAD 136 
#define  ARM_SPE_CONTEXT 135 
#define  ARM_SPE_COUNTER 134 
#define  ARM_SPE_DATA_SOURCE 133 
#define  ARM_SPE_END 132 
#define  ARM_SPE_EVENTS 131 
#define  ARM_SPE_OP_TYPE 130 
#define  ARM_SPE_PAD 129 
#define  ARM_SPE_TIMESTAMP 128 
 int EL_FLAG ; 
 int NS_FLAG ; 
 char* arm_spe_pkt_name (int) ; 
 int snprintf (char*,size_t,char*,...) ; 

int arm_spe_pkt_desc(const struct arm_spe_pkt *packet, char *buf,
		     size_t buf_len)
{
	int ret, ns, el, idx = packet->index;
	unsigned long long payload = packet->payload;
	const char *name = arm_spe_pkt_name(packet->type);

	switch (packet->type) {
	case ARM_SPE_BAD:
	case ARM_SPE_PAD:
	case ARM_SPE_END:
		return snprintf(buf, buf_len, "%s", name);
	case ARM_SPE_EVENTS: {
		size_t blen = buf_len;

		ret = 0;
		ret = snprintf(buf, buf_len, "EV");
		buf += ret;
		blen -= ret;
		if (payload & 0x1) {
			ret = snprintf(buf, buf_len, " EXCEPTION-GEN");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x2) {
			ret = snprintf(buf, buf_len, " RETIRED");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x4) {
			ret = snprintf(buf, buf_len, " L1D-ACCESS");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x8) {
			ret = snprintf(buf, buf_len, " L1D-REFILL");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x10) {
			ret = snprintf(buf, buf_len, " TLB-ACCESS");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x20) {
			ret = snprintf(buf, buf_len, " TLB-REFILL");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x40) {
			ret = snprintf(buf, buf_len, " NOT-TAKEN");
			buf += ret;
			blen -= ret;
		}
		if (payload & 0x80) {
			ret = snprintf(buf, buf_len, " MISPRED");
			buf += ret;
			blen -= ret;
		}
		if (idx > 1) {
			if (payload & 0x100) {
				ret = snprintf(buf, buf_len, " LLC-ACCESS");
				buf += ret;
				blen -= ret;
			}
			if (payload & 0x200) {
				ret = snprintf(buf, buf_len, " LLC-REFILL");
				buf += ret;
				blen -= ret;
			}
			if (payload & 0x400) {
				ret = snprintf(buf, buf_len, " REMOTE-ACCESS");
				buf += ret;
				blen -= ret;
			}
		}
		if (ret < 0)
			return ret;
		blen -= ret;
		return buf_len - blen;
	}
	case ARM_SPE_OP_TYPE:
		switch (idx) {
		case 0:	return snprintf(buf, buf_len, "%s", payload & 0x1 ?
					"COND-SELECT" : "INSN-OTHER");
		case 1:	{
			size_t blen = buf_len;

			if (payload & 0x1)
				ret = snprintf(buf, buf_len, "ST");
			else
				ret = snprintf(buf, buf_len, "LD");
			buf += ret;
			blen -= ret;
			if (payload & 0x2) {
				if (payload & 0x4) {
					ret = snprintf(buf, buf_len, " AT");
					buf += ret;
					blen -= ret;
				}
				if (payload & 0x8) {
					ret = snprintf(buf, buf_len, " EXCL");
					buf += ret;
					blen -= ret;
				}
				if (payload & 0x10) {
					ret = snprintf(buf, buf_len, " AR");
					buf += ret;
					blen -= ret;
				}
			} else if (payload & 0x4) {
				ret = snprintf(buf, buf_len, " SIMD-FP");
				buf += ret;
				blen -= ret;
			}
			if (ret < 0)
				return ret;
			blen -= ret;
			return buf_len - blen;
		}
		case 2:	{
			size_t blen = buf_len;

			ret = snprintf(buf, buf_len, "B");
			buf += ret;
			blen -= ret;
			if (payload & 0x1) {
				ret = snprintf(buf, buf_len, " COND");
				buf += ret;
				blen -= ret;
			}
			if (payload & 0x2) {
				ret = snprintf(buf, buf_len, " IND");
				buf += ret;
				blen -= ret;
			}
			if (ret < 0)
				return ret;
			blen -= ret;
			return buf_len - blen;
			}
		default: return 0;
		}
	case ARM_SPE_DATA_SOURCE:
	case ARM_SPE_TIMESTAMP:
		return snprintf(buf, buf_len, "%s %lld", name, payload);
	case ARM_SPE_ADDRESS:
		switch (idx) {
		case 0:
		case 1: ns = !!(packet->payload & NS_FLAG);
			el = (packet->payload & EL_FLAG) >> 61;
			payload &= ~(0xffULL << 56);
			return snprintf(buf, buf_len, "%s 0x%llx el%d ns=%d",
				        (idx == 1) ? "TGT" : "PC", payload, el, ns);
		case 2:	return snprintf(buf, buf_len, "VA 0x%llx", payload);
		case 3:	ns = !!(packet->payload & NS_FLAG);
			payload &= ~(0xffULL << 56);
			return snprintf(buf, buf_len, "PA 0x%llx ns=%d",
					payload, ns);
		default: return 0;
		}
	case ARM_SPE_CONTEXT:
		return snprintf(buf, buf_len, "%s 0x%lx el%d", name,
				(unsigned long)payload, idx + 1);
	case ARM_SPE_COUNTER: {
		size_t blen = buf_len;

		ret = snprintf(buf, buf_len, "%s %d ", name,
			       (unsigned short)payload);
		buf += ret;
		blen -= ret;
		switch (idx) {
		case 0:	ret = snprintf(buf, buf_len, "TOT"); break;
		case 1:	ret = snprintf(buf, buf_len, "ISSUE"); break;
		case 2:	ret = snprintf(buf, buf_len, "XLAT"); break;
		default: ret = 0;
		}
		if (ret < 0)
			return ret;
		blen -= ret;
		return buf_len - blen;
	}
	default:
		break;
	}

	return snprintf(buf, buf_len, "%s 0x%llx (%d)",
			name, payload, packet->index);
}