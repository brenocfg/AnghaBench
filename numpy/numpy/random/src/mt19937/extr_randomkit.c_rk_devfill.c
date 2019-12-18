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
typedef  int /*<<< orphan*/  rk_error ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 int /*<<< orphan*/  CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptGenRandom (int /*<<< orphan*/ ,size_t,unsigned char*) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  RK_DEV_RANDOM ; 
 int /*<<< orphan*/  RK_DEV_URANDOM ; 
 int /*<<< orphan*/  RK_ENODEV ; 
 int /*<<< orphan*/  RK_NOERR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (void*,size_t,int,int /*<<< orphan*/ *) ; 

rk_error rk_devfill(void *buffer, size_t size, int strong) {
#ifndef _WIN32
  FILE *rfile;
  int done;

  if (strong) {
    rfile = fopen(RK_DEV_RANDOM, "rb");
  } else {
    rfile = fopen(RK_DEV_URANDOM, "rb");
  }
  if (rfile == NULL) {
    return RK_ENODEV;
  }
  done = fread(buffer, size, 1, rfile);
  fclose(rfile);
  if (done) {
    return RK_NOERR;
  }
#else

#ifndef RK_NO_WINCRYPT
  HCRYPTPROV hCryptProv;
  BOOL done;

  if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL,
                           CRYPT_VERIFYCONTEXT) ||
      !hCryptProv) {
    return RK_ENODEV;
  }
  done = CryptGenRandom(hCryptProv, size, (unsigned char *)buffer);
  CryptReleaseContext(hCryptProv, 0);
  if (done) {
    return RK_NOERR;
  }
#endif

#endif
  return RK_ENODEV;
}