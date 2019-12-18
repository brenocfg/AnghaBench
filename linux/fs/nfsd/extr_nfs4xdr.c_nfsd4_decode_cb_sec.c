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
typedef  int u32 ;
struct user_namespace {int dummy; } ;
struct nfsd4_compoundargs {int /*<<< orphan*/  rqstp; } ;
struct nfsd4_cb_sec {int flavor; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
#define  RPC_AUTH_GSS 130 
#define  RPC_AUTH_NULL 129 
#define  RPC_AUTH_UNIX 128 
 int /*<<< orphan*/  SAVEMEM (char*,int) ; 
 int /*<<< orphan*/  XDR_QUADLEN (int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (struct user_namespace*,int) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int) ; 
 struct user_namespace* nfsd_user_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_inval ; 
 scalar_t__ p ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 nfsd4_decode_cb_sec(struct nfsd4_compoundargs *argp, struct nfsd4_cb_sec *cbs)
{
	DECODE_HEAD;
	struct user_namespace *userns = nfsd_user_namespace(argp->rqstp);
	u32 dummy, uid, gid;
	char *machine_name;
	int i;
	int nr_secflavs;

	/* callback_sec_params4 */
	READ_BUF(4);
	nr_secflavs = be32_to_cpup(p++);
	if (nr_secflavs)
		cbs->flavor = (u32)(-1);
	else
		/* Is this legal? Be generous, take it to mean AUTH_NONE: */
		cbs->flavor = 0;
	for (i = 0; i < nr_secflavs; ++i) {
		READ_BUF(4);
		dummy = be32_to_cpup(p++);
		switch (dummy) {
		case RPC_AUTH_NULL:
			/* Nothing to read */
			if (cbs->flavor == (u32)(-1))
				cbs->flavor = RPC_AUTH_NULL;
			break;
		case RPC_AUTH_UNIX:
			READ_BUF(8);
			/* stamp */
			dummy = be32_to_cpup(p++);

			/* machine name */
			dummy = be32_to_cpup(p++);
			READ_BUF(dummy);
			SAVEMEM(machine_name, dummy);

			/* uid, gid */
			READ_BUF(8);
			uid = be32_to_cpup(p++);
			gid = be32_to_cpup(p++);

			/* more gids */
			READ_BUF(4);
			dummy = be32_to_cpup(p++);
			READ_BUF(dummy * 4);
			if (cbs->flavor == (u32)(-1)) {
				kuid_t kuid = make_kuid(userns, uid);
				kgid_t kgid = make_kgid(userns, gid);
				if (uid_valid(kuid) && gid_valid(kgid)) {
					cbs->uid = kuid;
					cbs->gid = kgid;
					cbs->flavor = RPC_AUTH_UNIX;
				} else {
					dprintk("RPC_AUTH_UNIX with invalid"
						"uid or gid ignoring!\n");
				}
			}
			break;
		case RPC_AUTH_GSS:
			dprintk("RPC_AUTH_GSS callback secflavor "
				"not supported!\n");
			READ_BUF(8);
			/* gcbp_service */
			dummy = be32_to_cpup(p++);
			/* gcbp_handle_from_server */
			dummy = be32_to_cpup(p++);
			READ_BUF(dummy);
			p += XDR_QUADLEN(dummy);
			/* gcbp_handle_from_client */
			READ_BUF(4);
			dummy = be32_to_cpup(p++);
			READ_BUF(dummy);
			break;
		default:
			dprintk("Illegal callback secflavor\n");
			return nfserr_inval;
		}
	}
	DECODE_TAIL;
}