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
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/ * RSA_new () ; 
 int key1 (int /*<<< orphan*/ *,unsigned char*) ; 
 int key2 (int /*<<< orphan*/ *,unsigned char*) ; 
 int key3 (int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int rsa_setkey(RSA** key, unsigned char* ctext, int idx)
{
    int clen = 0;
    *key = RSA_new();
    switch (idx) {
    case 0:
        clen = key1(*key, ctext);
        break;
    case 1:
        clen = key2(*key, ctext);
        break;
    case 2:
        clen = key3(*key, ctext);
        break;
    }
    return clen;
}