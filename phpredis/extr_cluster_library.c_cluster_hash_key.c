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

/* Variables and functions */
 unsigned short REDIS_CLUSTER_MOD ; 
 unsigned short crc16 (char const*,int) ; 

unsigned short cluster_hash_key(const char *key, int len) {
    int s, e;

    // Find first occurrence of {, if any
    for (s = 0; s < len; s++) {
        if (key[s]=='{') break;
    }

    // There is no '{', hash everything
    if (s == len) return crc16(key, len) & REDIS_CLUSTER_MOD;

    // Found it, look for a tailing '}'
    for (e =s + 1; e < len; e++) {
        if (key[e] == '}') break;
    }

    // Hash the whole key if we don't find a tailing } or if {} is empty
    if (e == len || e == s+1) return crc16(key, len) & REDIS_CLUSTER_MOD;

    // Hash just the bit betweeen { and }
    return crc16((char*)key+s+1,e-s-1) & REDIS_CLUSTER_MOD;
}