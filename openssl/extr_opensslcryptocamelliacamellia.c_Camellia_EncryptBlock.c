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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  KEY_TABLE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  Camellia_EncryptBlock_Rounds (int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

void Camellia_EncryptBlock(int keyBitLength, const u8 plaintext[],
                           const KEY_TABLE_TYPE keyTable, u8 ciphertext[])
{
    Camellia_EncryptBlock_Rounds(keyBitLength == 128 ? 3 : 4,
                                 plaintext, keyTable, ciphertext);
}