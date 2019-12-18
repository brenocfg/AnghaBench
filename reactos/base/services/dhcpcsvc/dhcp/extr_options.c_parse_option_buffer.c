#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct packet {int options_valid; TYPE_1__* options; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {unsigned char* data; int len; } ;

/* Variables and functions */
 unsigned char DHO_END ; 
 int DHO_PAD ; 
 scalar_t__ bad_options ; 
 scalar_t__ bad_options_max ; 
 unsigned char* calloc (int,int) ; 
 TYPE_2__* dhcp_options ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

void
parse_option_buffer(struct packet *packet,
    unsigned char *buffer, int length)
{
	unsigned char *s, *t, *end = buffer + length;
	int len, code;

	for (s = buffer; *s != DHO_END && s < end; ) {
		code = s[0];

		/* Pad options don't have a length - just skip them. */
		if (code == DHO_PAD) {
			s++;
			continue;
		}
		if (s + 2 > end) {
			len = 65536;
			goto bogus;
		}

		/*
		 * All other fields (except end, see above) have a
		 * one-byte length.
		 */
		len = s[1];

		/*
		 * If the length is outrageous, silently skip the rest,
		 * and mark the packet bad. Unfortunately some crappy
		 * dhcp servers always seem to give us garbage on the
		 * end of a packet. so rather than keep refusing, give
		 * up and try to take one after seeing a few without
		 * anything good.
		 */
		if (s + len + 2 > end) {
		    bogus:
			bad_options++;
			warning("option %s (%d) %s.",
			    dhcp_options[code].name, len,
			    "larger than buffer");
			if (bad_options == bad_options_max) {
				packet->options_valid = 1;
				bad_options = 0;
				warning("Many bogus options seen in offers. "
				    "Taking this offer in spite of bogus "
				    "options - hope for the best!");
			} else {
				warning("rejecting bogus offer.");
				packet->options_valid = 0;
			}
			return;
		}
		/*
		 * If we haven't seen this option before, just make
		 * space for it and copy it there.
		 */
		if (!packet->options[code].data) {
			if (!(t = calloc(1, len + 1)))
				error("Can't allocate storage for option %s.",
				    dhcp_options[code].name);
			/*
			 * Copy and NUL-terminate the option (in case
			 * it's an ASCII string.
			 */
			memcpy(t, &s[2], len);
			t[len] = 0;
			packet->options[code].len = len;
			packet->options[code].data = t;
		} else {
			/*
			 * If it's a repeat, concatenate it to whatever
			 * we last saw.   This is really only required
			 * for clients, but what the heck...
			 */
			t = calloc(1, len + packet->options[code].len + 1);
			if (!t) {
				error("Can't expand storage for option %s.",
				    dhcp_options[code].name);
                                return;
                        }
			memcpy(t, packet->options[code].data,
				packet->options[code].len);
			memcpy(t + packet->options[code].len,
				&s[2], len);
			packet->options[code].len += len;
			t[packet->options[code].len] = 0;
			free(packet->options[code].data);
			packet->options[code].data = t;
		}
		s += len + 2;
	}
	packet->options_valid = 1;
}