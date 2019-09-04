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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int dummy; } ;
typedef  struct timeval pid_t ;
typedef  int /*<<< orphan*/  pid ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int DIGEST_SIZE ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,struct timeval*,int) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int RAND_bytes (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SALT_SIZE ; 
 struct timeval getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_salt(unsigned char *salt) {
    EVP_MD_CTX ctx;
    unsigned char md[DIGEST_SIZE];
    struct timeval tv;
    pid_t pid;
    unsigned int rlen;

    if (RAND_bytes(salt, SALT_SIZE) == 1) {
        return;
    }
    gettimeofday(&tv, 0);
    pid = getpid();
    EVP_DigestInit(&ctx, EVP_sha1());
    EVP_DigestUpdate(&ctx, &tv, sizeof(tv));
    EVP_DigestUpdate(&ctx, &pid, sizeof(pid));
    EVP_DigestFinal(&ctx, md, &rlen);
    memcpy(salt, md, SALT_SIZE);
}