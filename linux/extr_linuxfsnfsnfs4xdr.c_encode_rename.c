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
struct xdr_stream {int dummy; } ;
struct qstr {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_RENAME ; 
 int /*<<< orphan*/  decode_rename_maxsz ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_string (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_rename(struct xdr_stream *xdr, const struct qstr *oldname, const struct qstr *newname, struct compound_hdr *hdr)
{
	encode_op_hdr(xdr, OP_RENAME, decode_rename_maxsz, hdr);
	encode_string(xdr, oldname->len, oldname->name);
	encode_string(xdr, newname->len, newname->name);
}