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
struct sip_header {int len; int clen; unsigned int (* match_len ) (struct nf_conn const*,char const*,char const*,int*) ;int /*<<< orphan*/  slen; scalar_t__ search; scalar_t__ cname; scalar_t__ name; } ;
struct nf_conn {int dummy; } ;
typedef  enum sip_header_types { ____Placeholder_sip_header_types } sip_header_types ;

/* Variables and functions */
 struct sip_header* ct_sip_hdrs ; 
 char* ct_sip_header_search (char const*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isalpha (char const) ; 
 char* sip_skip_whitespace (char const*,char const*) ; 
 scalar_t__ strncasecmp (char const*,scalar_t__,int) ; 
 unsigned int stub1 (struct nf_conn const*,char const*,char const*,int*) ; 

int ct_sip_get_header(const struct nf_conn *ct, const char *dptr,
		      unsigned int dataoff, unsigned int datalen,
		      enum sip_header_types type,
		      unsigned int *matchoff, unsigned int *matchlen)
{
	const struct sip_header *hdr = &ct_sip_hdrs[type];
	const char *start = dptr, *limit = dptr + datalen;
	int shift = 0;

	for (dptr += dataoff; dptr < limit; dptr++) {
		/* Find beginning of line */
		if (*dptr != '\r' && *dptr != '\n')
			continue;
		if (++dptr >= limit)
			break;
		if (*(dptr - 1) == '\r' && *dptr == '\n') {
			if (++dptr >= limit)
				break;
		}

		/* Skip continuation lines */
		if (*dptr == ' ' || *dptr == '\t')
			continue;

		/* Find header. Compact headers must be followed by a
		 * non-alphabetic character to avoid mismatches. */
		if (limit - dptr >= hdr->len &&
		    strncasecmp(dptr, hdr->name, hdr->len) == 0)
			dptr += hdr->len;
		else if (hdr->cname && limit - dptr >= hdr->clen + 1 &&
			 strncasecmp(dptr, hdr->cname, hdr->clen) == 0 &&
			 !isalpha(*(dptr + hdr->clen)))
			dptr += hdr->clen;
		else
			continue;

		/* Find and skip colon */
		dptr = sip_skip_whitespace(dptr, limit);
		if (dptr == NULL)
			break;
		if (*dptr != ':' || ++dptr >= limit)
			break;

		/* Skip whitespace after colon */
		dptr = sip_skip_whitespace(dptr, limit);
		if (dptr == NULL)
			break;

		*matchoff = dptr - start;
		if (hdr->search) {
			dptr = ct_sip_header_search(dptr, limit, hdr->search,
						    hdr->slen);
			if (!dptr)
				return -1;
			dptr += hdr->slen;
		}

		*matchlen = hdr->match_len(ct, dptr, limit, &shift);
		if (!*matchlen)
			return -1;
		*matchoff = dptr - start + shift;
		return 1;
	}
	return 0;
}