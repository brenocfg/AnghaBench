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
struct sctp_rtoinfo {int srto_initial; int srto_max; int srto_min; int sasoc_asocmaxrxt; } ;
struct sctp_assocparams {int srto_initial; int srto_max; int srto_min; int sasoc_asocmaxrxt; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_dgram_sctp (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_ASSOCINFO ; 
 int /*<<< orphan*/  SCTP_RTOINFO ; 
 int /*<<< orphan*/  memset (struct sctp_rtoinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int set_sock_as_sctp(int sock)
{
    struct sctp_assocparams assocparams;
    struct sctp_rtoinfo rto_info;
    BIO *tmpbio;

    /*
     * To allow tests to fail fast (within a second or so), reduce the
     * retransmission timeouts and the number of retransmissions.
     */
    memset(&rto_info, 0, sizeof(struct sctp_rtoinfo));
    rto_info.srto_initial = 100;
    rto_info.srto_max = 200;
    rto_info.srto_min = 50;
    (void)setsockopt(sock, IPPROTO_SCTP, SCTP_RTOINFO,
                     (const void *)&rto_info, sizeof(struct sctp_rtoinfo));
    memset(&assocparams, 0, sizeof(struct sctp_assocparams));
    assocparams.sasoc_asocmaxrxt = 2;
    (void)setsockopt(sock, IPPROTO_SCTP, SCTP_ASSOCINFO,
                     (const void *)&assocparams,
                     sizeof(struct sctp_assocparams));

    /*
     * For SCTP we have to set various options on the socket prior to
     * connecting. This is done automatically by BIO_new_dgram_sctp().
     * We don't actually need the created BIO though so we free it again
     * immediately.
     */
    tmpbio = BIO_new_dgram_sctp(sock, BIO_NOCLOSE);

    if (tmpbio == NULL)
        return 0;
    BIO_free(tmpbio);

    return 1;
}