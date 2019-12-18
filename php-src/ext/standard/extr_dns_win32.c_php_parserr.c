#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_27__ {char* val; char* len; } ;
typedef  TYPE_6__ zend_string ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
typedef  char u_char ;
struct TYPE_30__ {size_t dwStringCount; int /*<<< orphan*/ * pStringArray; } ;
struct TYPE_22__ {int /*<<< orphan*/  S_addr; } ;
struct TYPE_29__ {TYPE_1__ S_un; } ;
struct TYPE_20__ {int wOrder; int wPreference; char* pFlags; char* pService; char* pRegularExpression; char* pReplacement; } ;
struct TYPE_18__ {int wPriority; int wWeight; int wPort; char* pNameTarget; } ;
struct TYPE_26__ {size_t* IP6Dword; } ;
struct TYPE_21__ {TYPE_5__ Ip6Address; } ;
struct TYPE_19__ {char* pNamePrimaryServer; char* pNameAdministrator; int dwSerialNo; int dwRefresh; int dwRetry; int dwExpire; int dwDefaultTtl; } ;
struct TYPE_24__ {char* pNameExchange; } ;
struct TYPE_23__ {int /*<<< orphan*/  IpAddress; } ;
struct TYPE_25__ {TYPE_12__ Naptr; TYPE_10__ Srv; TYPE_13__ AAAA; TYPE_11__ Soa; TYPE_9__ TXT; TYPE_3__ MX; TYPE_2__ A; } ;
struct TYPE_28__ {int wType; int dwTtl; char* pName; TYPE_4__ Data; scalar_t__ wDataLength; } ;
typedef  TYPE_7__* PDNS_RECORD ;
typedef  TYPE_8__ IN_ADDR ;
typedef  size_t DWORD ;
typedef  TYPE_9__ DNS_TXT_DATA ;
typedef  TYPE_10__ DNS_SRV_DATA ;
typedef  TYPE_11__ DNS_SOA_DATA ;
typedef  TYPE_12__ DNS_NAPTR_DATA ;
typedef  TYPE_13__ DNS_AAAA_DATA ;

/* Variables and functions */
#define  DNS_TYPE_A 139 
#define  DNS_TYPE_A6 138 
#define  DNS_TYPE_AAAA 137 
 int DNS_TYPE_ANY ; 
#define  DNS_TYPE_CNAME 136 
#define  DNS_TYPE_HINFO 135 
#define  DNS_TYPE_MX 134 
#define  DNS_TYPE_NAPTR 133 
#define  DNS_TYPE_NS 132 
#define  DNS_TYPE_PTR 131 
#define  DNS_TYPE_SOA 130 
#define  DNS_TYPE_SRV 129 
#define  DNS_TYPE_TEXT 128 
 int /*<<< orphan*/  HIWORD (size_t) ; 
 int /*<<< orphan*/  LOWORD (size_t) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_assoc_str (int /*<<< orphan*/ *,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_assoc_stringl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 unsigned short htons (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (TYPE_8__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 TYPE_6__* zend_string_safe_alloc (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_parserr(PDNS_RECORD pRec, int type_to_fetch, int store, int raw, zval *subarray)
{
	int type;
	u_long ttl;

	type = pRec->wType;
	ttl = pRec->dwTtl;

	ZVAL_UNDEF(subarray);

	if (type_to_fetch != DNS_TYPE_ANY && type != type_to_fetch) {
		return;
	}

	if (!store) {
		return;
	}

	array_init(subarray);

	add_assoc_string(subarray, "host", pRec->pName);
	add_assoc_string(subarray, "class", "IN");
	add_assoc_long(subarray, "ttl", ttl);

	if (raw) {
		add_assoc_long(subarray, "type", type);
		add_assoc_stringl(subarray, "data", (char*) &pRec->Data, (uint32_t) pRec->wDataLength);
		return;
	}

	switch (type) {
		case DNS_TYPE_A: {
			IN_ADDR ipaddr;
			ipaddr.S_un.S_addr = (pRec->Data.A.IpAddress);
			add_assoc_string(subarray, "type", "A");
			add_assoc_string(subarray, "ip", inet_ntoa(ipaddr));
			break;
		}

		case DNS_TYPE_MX:
			add_assoc_string(subarray, "type", "MX");
			add_assoc_long(subarray, "pri", pRec->Data.Srv.wPriority);
			/* no break; */

		case DNS_TYPE_CNAME:
			if (type == DNS_TYPE_CNAME) {
				add_assoc_string(subarray, "type", "CNAME");
			}
			/* no break; */

		case DNS_TYPE_NS:
			if (type == DNS_TYPE_NS) {
				add_assoc_string(subarray, "type", "NS");
			}
			/* no break; */

		case DNS_TYPE_PTR:
			if (type == DNS_TYPE_PTR) {
				add_assoc_string(subarray, "type", "PTR");
			}
			add_assoc_string(subarray, "target", pRec->Data.MX.pNameExchange);
			break;

		/* Not available on windows, the query is possible but there is no DNS_HINFO_DATA structure */
		case DNS_TYPE_HINFO:
		case DNS_TYPE_TEXT:
			{
				DWORD i = 0;
				DNS_TXT_DATA *data_txt = &pRec->Data.TXT;
				DWORD count = data_txt->dwStringCount;
				zend_string *txt;
				char *txt_dst;
				size_t txt_len = 0;
				zval entries;

				add_assoc_string(subarray, "type", "TXT");

				array_init(&entries);

				for (i = 0; i < count; i++) {
					txt_len += strlen(data_txt->pStringArray[i]) + 1;
				}

				txt = zend_string_safe_alloc(txt_len, 2, 0, 0);
				txt_dst = txt->val;
				for (i = 0; i < count; i++) {
					size_t len = strlen(data_txt->pStringArray[i]);
					memcpy(txt_dst, data_txt->pStringArray[i], len);
					add_next_index_stringl(&entries, data_txt->pStringArray[i], len);
					txt_dst += len;
				}
				txt->len = txt_dst - txt->val;
				add_assoc_str(subarray, "txt", txt);
				add_assoc_zval(subarray, "entries", &entries);
			}
			break;

		case DNS_TYPE_SOA:
			{
				DNS_SOA_DATA *data_soa = &pRec->Data.Soa;

				add_assoc_string(subarray, "type", "SOA");

				add_assoc_string(subarray, "mname", data_soa->pNamePrimaryServer);
				add_assoc_string(subarray, "rname", data_soa->pNameAdministrator);
				add_assoc_long(subarray, "serial", data_soa->dwSerialNo);
				add_assoc_long(subarray, "refresh", data_soa->dwRefresh);
				add_assoc_long(subarray, "retry", data_soa->dwRetry);
				add_assoc_long(subarray, "expire", data_soa->dwExpire);
				add_assoc_long(subarray, "minimum-ttl", data_soa->dwDefaultTtl);
			}
			break;

		case DNS_TYPE_AAAA:
			{
				DNS_AAAA_DATA *data_aaaa = &pRec->Data.AAAA;
				char buf[sizeof("AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA")];
				char *tp = buf;
				int i;
				unsigned short out[8];
				int have_v6_break = 0, in_v6_break = 0;

				for (i = 0; i < 4; ++i) {
					DWORD chunk = data_aaaa->Ip6Address.IP6Dword[i];
					out[i * 2]     = htons(LOWORD(chunk));
					out[i * 2 + 1] = htons(HIWORD(chunk));
				}

				for(i=0; i < 8; i++) {
					if (out[i] != 0) {
						if (tp > (u_char *)buf) {
							in_v6_break = 0;
							tp[0] = ':';
							tp++;
						}
						tp += sprintf((char*)tp,"%x", out[i]);
					} else {
						if (!have_v6_break) {
							have_v6_break = 1;
							in_v6_break = 1;
							tp[0] = ':';
							tp++;
						} else if (!in_v6_break) {
							tp[0] = ':';
							tp++;
							tp[0] = '0';
							tp++;
						}
					}
				}

				if (have_v6_break && in_v6_break) {
					tp[0] = ':';
					tp++;
				}
				tp[0] = '\0';

				add_assoc_string(subarray, "type", "AAAA");
				add_assoc_string(subarray, "ipv6", buf);
			}
			break;

#if 0
		/* Won't be implemented. A6 is deprecated. (Pierre) */
		case DNS_TYPE_A6:
			break;
#endif

		case DNS_TYPE_SRV:
			{
				DNS_SRV_DATA *data_srv = &pRec->Data.Srv;

				add_assoc_string(subarray, "type", "SRV");
				add_assoc_long(subarray, "pri", data_srv->wPriority);
				add_assoc_long(subarray, "weight", data_srv->wWeight);
				add_assoc_long(subarray, "port", data_srv->wPort);
				add_assoc_string(subarray, "target", data_srv->pNameTarget);
			}
			break;

		case DNS_TYPE_NAPTR:
			{
				DNS_NAPTR_DATA * data_naptr = &pRec->Data.Naptr;

				add_assoc_string(subarray, "type", "NAPTR");
				add_assoc_long(subarray, "order", data_naptr->wOrder);
				add_assoc_long(subarray, "pref", data_naptr->wPreference);
				add_assoc_string(subarray, "flags", data_naptr->pFlags);
				add_assoc_string(subarray, "services", data_naptr->pService);
				add_assoc_string(subarray, "regex", data_naptr->pRegularExpression);
				add_assoc_string(subarray, "replacement", data_naptr->pReplacement);
			}
			break;

		default:
			/* unknown type */
			ZVAL_UNDEF(subarray);
			return;
	}

}