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
struct CertDecode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_push (struct CertDecode*,int,size_t) ; 
 int /*<<< orphan*/  memset (struct CertDecode*,int /*<<< orphan*/ ,int) ; 

void
x509_decode_init(struct CertDecode *x, size_t length)
{
    memset(x, 0, sizeof(*x));
    ASN1_push(x, 0xFFFFFFFF, length);
}