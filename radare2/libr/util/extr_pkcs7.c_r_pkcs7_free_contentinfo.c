#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  contentType; int /*<<< orphan*/  content; } ;
typedef  TYPE_1__ RPKCS7ContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  r_asn1_free_binary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asn1_free_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_pkcs7_free_contentinfo(RPKCS7ContentInfo *ci) {
	if (ci) {
		r_asn1_free_binary (ci->content);
		r_asn1_free_string (ci->contentType);
		// Used internally pkcs #7, so it shouldn't free ci.
	}
}