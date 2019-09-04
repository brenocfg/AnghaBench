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
struct sctp_shared_key {int dummy; } ;
struct sctp_auth_bytes {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sctp_auth_bytes* sctp_auth_asoc_set_secret (struct sctp_shared_key*,struct sctp_auth_bytes*,struct sctp_auth_bytes*,int /*<<< orphan*/ ) ; 
 int sctp_auth_compare_vectors (struct sctp_auth_bytes*,struct sctp_auth_bytes*) ; 
 int /*<<< orphan*/  sctp_auth_key_put (struct sctp_auth_bytes*) ; 
 struct sctp_auth_bytes* sctp_auth_make_local_vector (struct sctp_association const*,int /*<<< orphan*/ ) ; 
 struct sctp_auth_bytes* sctp_auth_make_peer_vector (struct sctp_association const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_auth_bytes *sctp_auth_asoc_create_secret(
				 const struct sctp_association *asoc,
				 struct sctp_shared_key *ep_key,
				 gfp_t gfp)
{
	struct sctp_auth_bytes *local_key_vector;
	struct sctp_auth_bytes *peer_key_vector;
	struct sctp_auth_bytes	*first_vector,
				*last_vector;
	struct sctp_auth_bytes	*secret = NULL;
	int	cmp;


	/* Now we need to build the key vectors
	 * SCTP-AUTH , Section 6.1
	 *    The RANDOM parameter, the CHUNKS parameter and the HMAC-ALGO
	 *    parameter sent by each endpoint are concatenated as byte vectors.
	 *    These parameters include the parameter type, parameter length, and
	 *    the parameter value, but padding is omitted; all padding MUST be
	 *    removed from this concatenation before proceeding with further
	 *    computation of keys.  Parameters which were not sent are simply
	 *    omitted from the concatenation process.  The resulting two vectors
	 *    are called the two key vectors.
	 */

	local_key_vector = sctp_auth_make_local_vector(asoc, gfp);
	peer_key_vector = sctp_auth_make_peer_vector(asoc, gfp);

	if (!peer_key_vector || !local_key_vector)
		goto out;

	/* Figure out the order in which the key_vectors will be
	 * added to the endpoint shared key.
	 * SCTP-AUTH, Section 6.1:
	 *   This is performed by selecting the numerically smaller key
	 *   vector and concatenating it to the endpoint pair shared
	 *   key, and then concatenating the numerically larger key
	 *   vector to that.  If the key vectors are equal as numbers
	 *   but differ in length, then the concatenation order is the
	 *   endpoint shared key, followed by the shorter key vector,
	 *   followed by the longer key vector.  Otherwise, the key
	 *   vectors are identical, and may be concatenated to the
	 *   endpoint pair key in any order.
	 */
	cmp = sctp_auth_compare_vectors(local_key_vector,
					peer_key_vector);
	if (cmp < 0) {
		first_vector = local_key_vector;
		last_vector = peer_key_vector;
	} else {
		first_vector = peer_key_vector;
		last_vector = local_key_vector;
	}

	secret = sctp_auth_asoc_set_secret(ep_key, first_vector, last_vector,
					    gfp);
out:
	sctp_auth_key_put(local_key_vector);
	sctp_auth_key_put(peer_key_vector);

	return secret;
}