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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ Min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int) ; 
 scalar_t__ strlen (char const*) ; 

uint32
string_hash(const void *key, Size keysize)
{
	/*
	 * If the string exceeds keysize-1 bytes, we want to hash only that many,
	 * because when it is copied into the hash table it will be truncated at
	 * that length.
	 */
	Size		s_len = strlen((const char *) key);

	s_len = Min(s_len, keysize - 1);
	return DatumGetUInt32(hash_any((const unsigned char *) key,
								   (int) s_len));
}