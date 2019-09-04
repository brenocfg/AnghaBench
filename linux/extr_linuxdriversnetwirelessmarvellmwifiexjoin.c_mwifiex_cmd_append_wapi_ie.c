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
struct mwifiex_private {int wapi_ie_len; struct mwifiex_ie_types_header* wapi_ie; int /*<<< orphan*/  adapter; } ;
struct mwifiex_ie_types_header {void* len; void* type; } ;
typedef  int /*<<< orphan*/  ie_header ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int TLV_TYPE_WAPI_IE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mwifiex_ie_types_header*,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_cmd_append_wapi_ie(struct mwifiex_private *priv, u8 **buffer)
{
	int retLen = 0;
	struct mwifiex_ie_types_header ie_header;

	/* Null Checks */
	if (buffer == NULL)
		return 0;
	if (*buffer == NULL)
		return 0;

	/*
	 * If there is a wapi ie buffer setup, append it to the return
	 *   parameter buffer pointer.
	 */
	if (priv->wapi_ie_len) {
		mwifiex_dbg(priv->adapter, CMD,
			    "cmd: append wapi ie %d to %p\n",
			    priv->wapi_ie_len, *buffer);

		/* Wrap the generic IE buffer with a pass through TLV type */
		ie_header.type = cpu_to_le16(TLV_TYPE_WAPI_IE);
		ie_header.len = cpu_to_le16(priv->wapi_ie_len);
		memcpy(*buffer, &ie_header, sizeof(ie_header));

		/* Increment the return size and the return buffer pointer
		   param */
		*buffer += sizeof(ie_header);
		retLen += sizeof(ie_header);

		/* Copy the wapi IE buffer to the output buffer, advance
		   pointer */
		memcpy(*buffer, priv->wapi_ie, priv->wapi_ie_len);

		/* Increment the return size and the return buffer pointer
		   param */
		*buffer += priv->wapi_ie_len;
		retLen += priv->wapi_ie_len;

	}
	/* return the length appended to the buffer */
	return retLen;
}