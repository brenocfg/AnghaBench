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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static char *cryptoSha1(char *data, unsigned int len) {
  SHA1_CTX ctx;
  SHA1Init(&ctx);
  SHA1Update(&ctx, data, len);

  uint8_t *digest = (uint8_t *) calloc(1,20);
  SHA1Final(digest, &ctx);
  return (char *) digest; // Requires free
}