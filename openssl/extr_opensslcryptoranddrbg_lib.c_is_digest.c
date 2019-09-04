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
#define  NID_sha1 138 
#define  NID_sha224 137 
#define  NID_sha256 136 
#define  NID_sha384 135 
#define  NID_sha3_224 134 
#define  NID_sha3_256 133 
#define  NID_sha3_384 132 
#define  NID_sha3_512 131 
#define  NID_sha512 130 
#define  NID_sha512_224 129 
#define  NID_sha512_256 128 

__attribute__((used)) static int is_digest(int type)
{
    switch (type) {
    case NID_sha1:
    case NID_sha224:
    case NID_sha256:
    case NID_sha384:
    case NID_sha512:
    case NID_sha512_224:
    case NID_sha512_256:
    case NID_sha3_224:
    case NID_sha3_256:
    case NID_sha3_384:
    case NID_sha3_512:
        return 1;
    default:
        return 0;
    }
}