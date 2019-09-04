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
#define  NID_sha1 131 
#define  NID_sha256 130 
#define  NID_sha384 129 
#define  NID_sha512 128 

int RSA_X931_hash_id(int nid)
{
    switch (nid) {
    case NID_sha1:
        return 0x33;

    case NID_sha256:
        return 0x34;

    case NID_sha384:
        return 0x36;

    case NID_sha512:
        return 0x35;

    }
    return -1;
}