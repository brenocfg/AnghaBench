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
struct intel_pt_pkt {unsigned long long payload; int type; int count; } ;

/* Variables and functions */
 unsigned long long BIT63 ; 
#define  INTEL_PT_BAD 159 
#define  INTEL_PT_BBP 158 
#define  INTEL_PT_BEP 157 
#define  INTEL_PT_BEP_IP 156 
#define  INTEL_PT_BIP 155 
#define  INTEL_PT_CBR 154 
#define  INTEL_PT_CYC 153 
#define  INTEL_PT_EXSTOP 152 
#define  INTEL_PT_EXSTOP_IP 151 
#define  INTEL_PT_FUP 150 
#define  INTEL_PT_MNT 149 
#define  INTEL_PT_MODE_EXEC 148 
#define  INTEL_PT_MODE_TSX 147 
#define  INTEL_PT_MTC 146 
#define  INTEL_PT_MWAIT 145 
#define  INTEL_PT_OVF 144 
#define  INTEL_PT_PAD 143 
#define  INTEL_PT_PIP 142 
#define  INTEL_PT_PSB 141 
#define  INTEL_PT_PSBEND 140 
#define  INTEL_PT_PTWRITE 139 
#define  INTEL_PT_PTWRITE_IP 138 
#define  INTEL_PT_PWRE 137 
#define  INTEL_PT_PWRX 136 
#define  INTEL_PT_TIP 135 
#define  INTEL_PT_TIP_PGD 134 
#define  INTEL_PT_TIP_PGE 133 
#define  INTEL_PT_TMA 132 
#define  INTEL_PT_TNT 131 
#define  INTEL_PT_TRACESTOP 130 
#define  INTEL_PT_TSC 129 
#define  INTEL_PT_VMCS 128 
 unsigned long long NR_FLAG ; 
 int /*<<< orphan*/  __fallthrough ; 
 char* intel_pt_pkt_name (int) ; 
 int snprintf (char*,size_t,char*,...) ; 

int intel_pt_pkt_desc(const struct intel_pt_pkt *packet, char *buf,
		      size_t buf_len)
{
	int ret, i, nr;
	unsigned long long payload = packet->payload;
	const char *name = intel_pt_pkt_name(packet->type);

	switch (packet->type) {
	case INTEL_PT_BAD:
	case INTEL_PT_PAD:
	case INTEL_PT_PSB:
	case INTEL_PT_PSBEND:
	case INTEL_PT_TRACESTOP:
	case INTEL_PT_OVF:
		return snprintf(buf, buf_len, "%s", name);
	case INTEL_PT_TNT: {
		size_t blen = buf_len;

		ret = snprintf(buf, blen, "%s ", name);
		if (ret < 0)
			return ret;
		buf += ret;
		blen -= ret;
		for (i = 0; i < packet->count; i++) {
			if (payload & BIT63)
				ret = snprintf(buf, blen, "T");
			else
				ret = snprintf(buf, blen, "N");
			if (ret < 0)
				return ret;
			buf += ret;
			blen -= ret;
			payload <<= 1;
		}
		ret = snprintf(buf, blen, " (%d)", packet->count);
		if (ret < 0)
			return ret;
		blen -= ret;
		return buf_len - blen;
	}
	case INTEL_PT_TIP_PGD:
	case INTEL_PT_TIP_PGE:
	case INTEL_PT_TIP:
	case INTEL_PT_FUP:
		if (!(packet->count))
			return snprintf(buf, buf_len, "%s no ip", name);
		__fallthrough;
	case INTEL_PT_CYC:
	case INTEL_PT_VMCS:
	case INTEL_PT_MTC:
	case INTEL_PT_MNT:
	case INTEL_PT_CBR:
	case INTEL_PT_TSC:
		return snprintf(buf, buf_len, "%s 0x%llx", name, payload);
	case INTEL_PT_TMA:
		return snprintf(buf, buf_len, "%s CTC 0x%x FC 0x%x", name,
				(unsigned)payload, packet->count);
	case INTEL_PT_MODE_EXEC:
		return snprintf(buf, buf_len, "%s %lld", name, payload);
	case INTEL_PT_MODE_TSX:
		return snprintf(buf, buf_len, "%s TXAbort:%u InTX:%u",
				name, (unsigned)(payload >> 1) & 1,
				(unsigned)payload & 1);
	case INTEL_PT_PIP:
		nr = packet->payload & NR_FLAG ? 1 : 0;
		payload &= ~NR_FLAG;
		ret = snprintf(buf, buf_len, "%s 0x%llx (NR=%d)",
			       name, payload, nr);
		return ret;
	case INTEL_PT_PTWRITE:
		return snprintf(buf, buf_len, "%s 0x%llx IP:0", name, payload);
	case INTEL_PT_PTWRITE_IP:
		return snprintf(buf, buf_len, "%s 0x%llx IP:1", name, payload);
	case INTEL_PT_BEP:
	case INTEL_PT_EXSTOP:
		return snprintf(buf, buf_len, "%s IP:0", name);
	case INTEL_PT_BEP_IP:
	case INTEL_PT_EXSTOP_IP:
		return snprintf(buf, buf_len, "%s IP:1", name);
	case INTEL_PT_MWAIT:
		return snprintf(buf, buf_len, "%s 0x%llx Hints 0x%x Extensions 0x%x",
				name, payload, (unsigned int)(payload & 0xff),
				(unsigned int)((payload >> 32) & 0x3));
	case INTEL_PT_PWRE:
		return snprintf(buf, buf_len, "%s 0x%llx HW:%u CState:%u Sub-CState:%u",
				name, payload, !!(payload & 0x80),
				(unsigned int)((payload >> 12) & 0xf),
				(unsigned int)((payload >> 8) & 0xf));
	case INTEL_PT_PWRX:
		return snprintf(buf, buf_len, "%s 0x%llx Last CState:%u Deepest CState:%u Wake Reason 0x%x",
				name, payload,
				(unsigned int)((payload >> 4) & 0xf),
				(unsigned int)(payload & 0xf),
				(unsigned int)((payload >> 8) & 0xf));
	case INTEL_PT_BBP:
		return snprintf(buf, buf_len, "%s SZ %s-byte Type 0x%llx",
				name, packet->count ? "4" : "8", payload);
	case INTEL_PT_BIP:
		return snprintf(buf, buf_len, "%s ID 0x%02x Value 0x%llx",
				name, packet->count, payload);
	default:
		break;
	}
	return snprintf(buf, buf_len, "%s 0x%llx (%d)",
			name, payload, packet->count);
}