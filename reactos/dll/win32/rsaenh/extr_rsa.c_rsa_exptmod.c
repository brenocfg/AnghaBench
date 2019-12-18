#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  N; int /*<<< orphan*/  e; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  qP; int /*<<< orphan*/  dQ; int /*<<< orphan*/  dP; } ;
typedef  TYPE_1__ rsa_key ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 int CRYPT_BUFFER_OVERFLOW ; 
 int CRYPT_OK ; 
 int CRYPT_PK_INVALID_SIZE ; 
 int CRYPT_PK_INVALID_TYPE ; 
 int CRYPT_PK_NOT_PRIVATE ; 
 scalar_t__ MP_LT ; 
 int MP_OKAY ; 
 int PK_PRIVATE ; 
 int PK_PUBLIC ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned long) ; 
 int mp_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_clear_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_init_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_mulmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_read_unsigned_bin (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int mp_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_to_unsigned_bin (int /*<<< orphan*/ *,unsigned char*) ; 
 unsigned long mp_unsigned_bin_size (int /*<<< orphan*/ *) ; 
 int mpi_to_ltc_error (int) ; 

int rsa_exptmod(const unsigned char *in,   unsigned long inlen,
                      unsigned char *out,  unsigned long *outlen, int which,
                      rsa_key *key)
{
   mp_int        tmp, tmpa, tmpb;
   unsigned long x;
   int           err;

   /* is the key of the right type for the operation? */
   if (which == PK_PRIVATE && (key->type != PK_PRIVATE)) {
      return CRYPT_PK_NOT_PRIVATE;
   }

   /* must be a private or public operation */
   if (which != PK_PRIVATE && which != PK_PUBLIC) {
      return CRYPT_PK_INVALID_TYPE;
   }

   /* init and copy into tmp */
   if ((err = mp_init_multi(&tmp, &tmpa, &tmpb, NULL)) != MP_OKAY)    { return mpi_to_ltc_error(err); }
   if ((err = mp_read_unsigned_bin(&tmp, in, (int)inlen)) != MP_OKAY) { goto error; }

   /* sanity check on the input */
   if (mp_cmp(&key->N, &tmp) == MP_LT) {
      err = CRYPT_PK_INVALID_SIZE;
      goto done;
   }

   /* are we using the private exponent and is the key optimized? */
   if (which == PK_PRIVATE) {
      /* tmpa = tmp^dP mod p */
      if ((err = mpi_to_ltc_error(mp_exptmod(&tmp, &key->dP, &key->p, &tmpa))) != MP_OKAY)    { goto error; }
      
      /* tmpb = tmp^dQ mod q */
      if ((err = mpi_to_ltc_error(mp_exptmod(&tmp, &key->dQ, &key->q, &tmpb))) != MP_OKAY)    { goto error; }

      /* tmp = (tmpa - tmpb) * qInv (mod p) */
      if ((err = mp_sub(&tmpa, &tmpb, &tmp)) != MP_OKAY)                    { goto error; }
      if ((err = mp_mulmod(&tmp, &key->qP, &key->p, &tmp)) != MP_OKAY)      { goto error; }

      /* tmp = tmpb + q * tmp */
      if ((err = mp_mul(&tmp, &key->q, &tmp)) != MP_OKAY)                   { goto error; }
      if ((err = mp_add(&tmp, &tmpb, &tmp)) != MP_OKAY)                     { goto error; }
   } else {
      /* exptmod it */
      if ((err = mp_exptmod(&tmp, &key->e, &key->N, &tmp)) != MP_OKAY) { goto error; }
   }

   /* read it back */
   x = (unsigned long)mp_unsigned_bin_size(&key->N);
   if (x > *outlen) {
      err = CRYPT_BUFFER_OVERFLOW;
      goto done;
   }
   *outlen = x;

   /* convert it */
   memset(out, 0, x);
   if ((err = mp_to_unsigned_bin(&tmp, out+(x-mp_unsigned_bin_size(&tmp)))) != MP_OKAY) { goto error; }

   /* clean up and return */
   err = CRYPT_OK;
   goto done;
error:
   err = mpi_to_ltc_error(err);
done:
   mp_clear_multi(&tmp, &tmpa, &tmpb, NULL);
   return err;
}