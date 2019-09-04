#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ tagIdent; } ;
struct fileIdentDesc {int lengthFileIdent; scalar_t__ lengthOfImpUse; TYPE_1__ descTag; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_IDENT_FID ; 
 int UDF_NAME_PAD ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  udf_debug (char*,int,...) ; 

struct fileIdentDesc *udf_get_fileident(void *buffer, int bufsize, int *offset)
{
	struct fileIdentDesc *fi;
	int lengthThisIdent;
	uint8_t *ptr;
	int padlen;

	if ((!buffer) || (!offset)) {
		udf_debug("invalidparms, buffer=%p, offset=%p\n",
			  buffer, offset);
		return NULL;
	}

	ptr = buffer;

	if ((*offset > 0) && (*offset < bufsize))
		ptr += *offset;
	fi = (struct fileIdentDesc *)ptr;
	if (fi->descTag.tagIdent != cpu_to_le16(TAG_IDENT_FID)) {
		udf_debug("0x%x != TAG_IDENT_FID\n",
			  le16_to_cpu(fi->descTag.tagIdent));
		udf_debug("offset: %d sizeof: %lu bufsize: %d\n",
			  *offset, (unsigned long)sizeof(struct fileIdentDesc),
			  bufsize);
		return NULL;
	}
	if ((*offset + sizeof(struct fileIdentDesc)) > bufsize)
		lengthThisIdent = sizeof(struct fileIdentDesc);
	else
		lengthThisIdent = sizeof(struct fileIdentDesc) +
			fi->lengthFileIdent + le16_to_cpu(fi->lengthOfImpUse);

	/* we need to figure padding, too! */
	padlen = lengthThisIdent % UDF_NAME_PAD;
	if (padlen)
		lengthThisIdent += (UDF_NAME_PAD - padlen);
	*offset = *offset + lengthThisIdent;

	return fi;
}