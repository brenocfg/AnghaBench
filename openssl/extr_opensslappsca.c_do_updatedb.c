#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__* db; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ CA_DB ;
typedef  TYPE_3__ ASN1_UTCTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_UTCTIME_free (TYPE_3__*) ; 
 TYPE_3__* ASN1_UTCTIME_new () ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*) ; 
 char DB_TYPE_EXP ; 
 char DB_TYPE_VAL ; 
 size_t DB_exp_date ; 
 size_t DB_serial ; 
 size_t DB_type ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/ * X509_gmtime_adj (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int sk_OPENSSL_PSTRING_num (int /*<<< orphan*/ ) ; 
 char** sk_OPENSSL_PSTRING_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int do_updatedb(CA_DB *db)
{
    ASN1_UTCTIME *a_tm = NULL;
    int i, cnt = 0;
    int db_y2k, a_y2k;          /* flags = 1 if y >= 2000 */
    char **rrow, *a_tm_s;

    a_tm = ASN1_UTCTIME_new();
    if (a_tm == NULL)
        return -1;

    /* get actual time and make a string */
    if (X509_gmtime_adj(a_tm, 0) == NULL) {
        ASN1_UTCTIME_free(a_tm);
        return -1;
    }
    a_tm_s = app_malloc(a_tm->length + 1, "time string");

    memcpy(a_tm_s, a_tm->data, a_tm->length);
    a_tm_s[a_tm->length] = '\0';

    if (strncmp(a_tm_s, "49", 2) <= 0)
        a_y2k = 1;
    else
        a_y2k = 0;

    for (i = 0; i < sk_OPENSSL_PSTRING_num(db->db->data); i++) {
        rrow = sk_OPENSSL_PSTRING_value(db->db->data, i);

        if (rrow[DB_type][0] == DB_TYPE_VAL) {
            /* ignore entries that are not valid */
            if (strncmp(rrow[DB_exp_date], "49", 2) <= 0)
                db_y2k = 1;
            else
                db_y2k = 0;

            if (db_y2k == a_y2k) {
                /* all on the same y2k side */
                if (strcmp(rrow[DB_exp_date], a_tm_s) <= 0) {
                    rrow[DB_type][0] = DB_TYPE_EXP;
                    rrow[DB_type][1] = '\0';
                    cnt++;

                    BIO_printf(bio_err, "%s=Expired\n", rrow[DB_serial]);
                }
            } else if (db_y2k < a_y2k) {
                rrow[DB_type][0] = DB_TYPE_EXP;
                rrow[DB_type][1] = '\0';
                cnt++;

                BIO_printf(bio_err, "%s=Expired\n", rrow[DB_serial]);
            }

        }
    }

    ASN1_UTCTIME_free(a_tm);
    OPENSSL_free(a_tm_s);
    return cnt;
}