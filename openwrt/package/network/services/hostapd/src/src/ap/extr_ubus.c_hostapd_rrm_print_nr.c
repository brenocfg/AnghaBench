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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int ssid_len; int /*<<< orphan*/  ssid; } ;
struct hostapd_neighbor_entry {int /*<<< orphan*/  nr; TYPE_1__ ssid; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACSTR ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  blobmsg_add_string_buffer (int /*<<< orphan*/ *) ; 
 char* blobmsg_alloc_string_buffer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  blobmsg_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hostapd_rrm_print_nr(struct hostapd_neighbor_entry *nr)
{
	const u8 *data;
	char *str;
	int len;

	blobmsg_printf(&b, "", MACSTR, MAC2STR(nr->bssid));

	str = blobmsg_alloc_string_buffer(&b, "", nr->ssid.ssid_len + 1);
	memcpy(str, nr->ssid.ssid, nr->ssid.ssid_len);
	str[nr->ssid.ssid_len] = 0;
	blobmsg_add_string_buffer(&b);

	len = wpabuf_len(nr->nr);
	str = blobmsg_alloc_string_buffer(&b, "", 2 * len + 1);
	wpa_snprintf_hex(str, 2 * len + 1, wpabuf_head_u8(nr->nr), len);
	blobmsg_add_string_buffer(&b);
}