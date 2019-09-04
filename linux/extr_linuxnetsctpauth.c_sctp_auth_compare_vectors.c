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
struct sctp_auth_bytes {int len; scalar_t__* data; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int abs (int) ; 
 int memcmp (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static int sctp_auth_compare_vectors(struct sctp_auth_bytes *vector1,
			      struct sctp_auth_bytes *vector2)
{
	int diff;
	int i;
	const __u8 *longer;

	diff = vector1->len - vector2->len;
	if (diff) {
		longer = (diff > 0) ? vector1->data : vector2->data;

		/* Check to see if the longer number is
		 * lead-zero padded.  If it is not, it
		 * is automatically larger numerically.
		 */
		for (i = 0; i < abs(diff); i++) {
			if (longer[i] != 0)
				return diff;
		}
	}

	/* lengths are the same, compare numbers */
	return memcmp(vector1->data, vector2->data, vector1->len);
}