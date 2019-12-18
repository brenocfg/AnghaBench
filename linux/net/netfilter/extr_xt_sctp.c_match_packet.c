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
typedef  int /*<<< orphan*/  u_int32_t ;
struct xt_sctp_info {int chunk_match_type; int flag_count; int /*<<< orphan*/  chunkmap; struct xt_sctp_flag_info* flag_info; } ;
struct xt_sctp_flag_info {int dummy; } ;
struct sk_buff {unsigned int len; } ;
struct sctp_chunkhdr {scalar_t__ length; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  _sch ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CHUNKMAP_CLEAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CHUNKMAP_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SCTP_CHUNKMAP_IS_CLEAR (int /*<<< orphan*/ *) ; 
 scalar_t__ SCTP_CHUNKMAP_IS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SCTP_CHUNK_MATCH_ALL 130 
#define  SCTP_CHUNK_MATCH_ANY 129 
#define  SCTP_CHUNK_MATCH_ONLY 128 
 scalar_t__ SCTP_PAD4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  match_flags (struct xt_sctp_flag_info const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct sctp_chunkhdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct sctp_chunkhdr*) ; 

__attribute__((used)) static inline bool
match_packet(const struct sk_buff *skb,
	     unsigned int offset,
	     const struct xt_sctp_info *info,
	     bool *hotdrop)
{
	u_int32_t chunkmapcopy[256 / sizeof (u_int32_t)];
	const struct sctp_chunkhdr *sch;
	struct sctp_chunkhdr _sch;
	int chunk_match_type = info->chunk_match_type;
	const struct xt_sctp_flag_info *flag_info = info->flag_info;
	int flag_count = info->flag_count;

#ifdef DEBUG
	int i = 0;
#endif

	if (chunk_match_type == SCTP_CHUNK_MATCH_ALL)
		SCTP_CHUNKMAP_COPY(chunkmapcopy, info->chunkmap);

	do {
		sch = skb_header_pointer(skb, offset, sizeof(_sch), &_sch);
		if (sch == NULL || sch->length == 0) {
			pr_debug("Dropping invalid SCTP packet.\n");
			*hotdrop = true;
			return false;
		}
#ifdef DEBUG
		pr_debug("Chunk num: %d\toffset: %d\ttype: %d\tlength: %d"
			 "\tflags: %x\n",
			 ++i, offset, sch->type, htons(sch->length),
			 sch->flags);
#endif
		offset += SCTP_PAD4(ntohs(sch->length));

		pr_debug("skb->len: %d\toffset: %d\n", skb->len, offset);

		if (SCTP_CHUNKMAP_IS_SET(info->chunkmap, sch->type)) {
			switch (chunk_match_type) {
			case SCTP_CHUNK_MATCH_ANY:
				if (match_flags(flag_info, flag_count,
					sch->type, sch->flags)) {
					return true;
				}
				break;

			case SCTP_CHUNK_MATCH_ALL:
				if (match_flags(flag_info, flag_count,
				    sch->type, sch->flags))
					SCTP_CHUNKMAP_CLEAR(chunkmapcopy, sch->type);
				break;

			case SCTP_CHUNK_MATCH_ONLY:
				if (!match_flags(flag_info, flag_count,
				    sch->type, sch->flags))
					return false;
				break;
			}
		} else {
			switch (chunk_match_type) {
			case SCTP_CHUNK_MATCH_ONLY:
				return false;
			}
		}
	} while (offset < skb->len);

	switch (chunk_match_type) {
	case SCTP_CHUNK_MATCH_ALL:
		return SCTP_CHUNKMAP_IS_CLEAR(chunkmapcopy);
	case SCTP_CHUNK_MATCH_ANY:
		return false;
	case SCTP_CHUNK_MATCH_ONLY:
		return true;
	}

	/* This will never be reached, but required to stop compiler whine */
	return false;
}