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
typedef  int /*<<< orphan*/  u16 ;
struct tcphdr {int doff; } ;

/* Variables and functions */
 int TCPOLEN_MSS ; 
#define  TCPOPT_EOL 129 
 int TCPOPT_MSS ; 
#define  TCPOPT_NOP 128 
 int /*<<< orphan*/  get_unaligned_be16 (unsigned char const*) ; 

__attribute__((used)) static u16 tcp_parse_mss_option(const struct tcphdr *th, u16 user_mss)
{
	const unsigned char *ptr = (const unsigned char *)(th + 1);
	int length = (th->doff * 4) - sizeof(struct tcphdr);
	u16 mss = 0;

	while (length > 0) {
		int opcode = *ptr++;
		int opsize;

		switch (opcode) {
		case TCPOPT_EOL:
			return mss;
		case TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			continue;
		default:
			if (length < 2)
				return mss;
			opsize = *ptr++;
			if (opsize < 2) /* "silly options" */
				return mss;
			if (opsize > length)
				return mss;	/* fail on partial options */
			if (opcode == TCPOPT_MSS && opsize == TCPOLEN_MSS) {
				u16 in_mss = get_unaligned_be16(ptr);

				if (in_mss) {
					if (user_mss && user_mss < in_mss)
						in_mss = user_mss;
					mss = in_mss;
				}
			}
			ptr += opsize - 2;
			length -= opsize;
		}
	}
	return mss;
}