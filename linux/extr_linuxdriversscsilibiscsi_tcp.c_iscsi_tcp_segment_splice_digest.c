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
struct iscsi_segment {int /*<<< orphan*/ * hash; int /*<<< orphan*/ * sg; scalar_t__ copied; void* size; int /*<<< orphan*/  total_size; void* digest_len; void* data; } ;

/* Variables and functions */
 void* ISCSI_DIGEST_SIZE ; 

__attribute__((used)) static inline void
iscsi_tcp_segment_splice_digest(struct iscsi_segment *segment, void *digest)
{
	segment->data = digest;
	segment->digest_len = ISCSI_DIGEST_SIZE;
	segment->total_size += ISCSI_DIGEST_SIZE;
	segment->size = ISCSI_DIGEST_SIZE;
	segment->copied = 0;
	segment->sg = NULL;
	segment->hash = NULL;
}