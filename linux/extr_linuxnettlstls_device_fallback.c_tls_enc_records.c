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
typedef  int /*<<< orphan*/  u64 ;
struct scatterlist {int dummy; } ;
struct scatter_walk {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 int tls_enc_record (struct aead_request*,struct crypto_aead*,char*,char*,int /*<<< orphan*/ ,struct scatter_walk*,struct scatter_walk*,int*) ; 

__attribute__((used)) static int tls_enc_records(struct aead_request *aead_req,
			   struct crypto_aead *aead, struct scatterlist *sg_in,
			   struct scatterlist *sg_out, char *aad, char *iv,
			   u64 rcd_sn, int len)
{
	struct scatter_walk out, in;
	int rc;

	scatterwalk_start(&in, sg_in);
	scatterwalk_start(&out, sg_out);

	do {
		rc = tls_enc_record(aead_req, aead, aad, iv,
				    cpu_to_be64(rcd_sn), &in, &out, &len);
		rcd_sn++;

	} while (rc == 0 && len);

	scatterwalk_done(&in, 0, 0);
	scatterwalk_done(&out, 1, 0);

	return rc;
}