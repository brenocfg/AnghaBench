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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LEN ; 
 int /*<<< orphan*/  RSANUMBYTES ; 
 int /*<<< orphan*/  RSA_verify (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,char*,int) ; 
 int SHA_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA_hash (int*,int,char*) ; 
 scalar_t__ buf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rsa_key ; 

int main() {
  FILE *f = fopen("../obj/panda.bin", "rb");
  int tlen = fread(buf, 1, MAX_LEN, f);
  fclose(f);
  printf("read %d\n", tlen);
  uint32_t *_app_start = (uint32_t *)buf;

  int len = _app_start[0];
  char digest[SHA_DIGEST_SIZE];
  SHA_hash(&_app_start[1], len-4, digest);
  printf("SHA hash done\n");

  if (!RSA_verify(&rsa_key, ((void*)&_app_start[0]) + len, RSANUMBYTES, digest, SHA_DIGEST_SIZE)) {
    printf("RSA fail\n");
  } else {
    printf("RSA match!!!\n");
  }

  return 0;
}