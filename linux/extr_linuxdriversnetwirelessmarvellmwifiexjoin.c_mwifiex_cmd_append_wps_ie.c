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
struct mwifiex_private {int wps_ie_len; struct mwifiex_ie_types_header* wps_ie; int /*<<< orphan*/  adapter; } ;
struct mwifiex_ie_types_header {void* len; void* type; } ;
typedef  int /*<<< orphan*/  ie_header ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int TLV_TYPE_PASSTHROUGH ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_ie_types_header*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mwifiex_ie_types_header*,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_cmd_append_wps_ie(struct mwifiex_private *priv, u8 **buffer)
{
	int retLen = 0;
	struct mwifiex_ie_types_header ie_header;

	if (!buffer || !*buffer)
		return 0;

	/*
	 * If there is a wps ie buffer setup, append it to the return
	 * parameter buffer pointer.
	 */
	if (priv->wps_ie_len) {
		mwifiex_dbg(priv->adapter, CMD,
			    "cmd: append wps ie %d to %p\n",
			    priv->wps_ie_len, *buffer);

		/* Wrap the generic IE buffer with a pass through TLV type */
		ie_header.type = cpu_to_le16(TLV_TYPE_PASSTHROUGH);
		ie_header.len = cpu_to_le16(priv->wps_ie_len);
		memcpy(*buffer, &ie_header, sizeof(ie_header));
		*buffer += sizeof(ie_header);
		retLen += sizeof(ie_header);

		memcpy(*buffer, priv->wps_ie, priv->wps_ie_len);
		*buffer += priv->wps_ie_len;
		retLen += priv->wps_ie_len;

	}

	kfree(priv->wps_ie);
	priv->wps_ie_len = 0;
	return retLen;
}