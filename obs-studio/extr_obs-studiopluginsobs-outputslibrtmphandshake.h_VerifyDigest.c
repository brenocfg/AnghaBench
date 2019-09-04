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

/* Variables and functions */
 int /*<<< orphan*/  CalculateDigest (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int SHA256_DIGEST_LENGTH ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
VerifyDigest(unsigned int digestPos, uint8_t *handshakeMessage, const uint8_t *key,
             size_t keyLen)
{
    uint8_t calcDigest[SHA256_DIGEST_LENGTH];

    CalculateDigest(digestPos, handshakeMessage, key, keyLen, calcDigest);

    return memcmp(&handshakeMessage[digestPos], calcDigest,
                  SHA256_DIGEST_LENGTH) == 0;
}