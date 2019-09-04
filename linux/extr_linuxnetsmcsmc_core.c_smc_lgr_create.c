#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct smcd_dev {int dummy; } ;
struct TYPE_5__ {struct smc_link_group* lgr; } ;
struct smc_sock {TYPE_2__ conn; scalar_t__ listen_smc; } ;
struct smc_link_group {int is_smcd; unsigned short vlan_id; int /*<<< orphan*/  list; struct smc_link* lnk; int /*<<< orphan*/ * peer_systemid; int /*<<< orphan*/  role; struct smcd_dev* smcd; int /*<<< orphan*/  peer_gid; int /*<<< orphan*/  conns_all; int /*<<< orphan*/  free_work; int /*<<< orphan*/  id; int /*<<< orphan*/ * rmbs; int /*<<< orphan*/ * sndbufs; int /*<<< orphan*/  conns_lock; int /*<<< orphan*/  rmbs_lock; int /*<<< orphan*/  sndbufs_lock; scalar_t__ sync_err; } ;
struct smc_link {size_t link_id; int ibport; int psn_initial; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  gid; struct smc_ib_device* smcibdev; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  state; } ;
struct smc_ib_device {int /*<<< orphan*/  initialized; TYPE_1__* pattr; } ;
typedef  int /*<<< orphan*/  rndvec ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; scalar_t__ num; } ;
struct TYPE_4__ {int /*<<< orphan*/  active_mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  SMC_CLNT ; 
 int /*<<< orphan*/  SMC_LGR_ID_SIZE ; 
 scalar_t__ SMC_LGR_NUM_INCR ; 
 int /*<<< orphan*/  SMC_LNK_ACTIVATING ; 
 int SMC_RMBE_SIZES ; 
 int /*<<< orphan*/  SMC_SERV ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  SMC_SYSTEMID_LEN ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  kfree (struct smc_link_group*) ; 
 struct smc_link_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int smc_ib_create_protection_domain (struct smc_link*) ; 
 int smc_ib_create_queue_pair (struct smc_link*) ; 
 int /*<<< orphan*/  smc_ib_dealloc_protection_domain (struct smc_link*) ; 
 int /*<<< orphan*/  smc_ib_destroy_queue_pair (struct smc_link*) ; 
 int smc_ib_determine_gid (struct smc_ib_device*,int,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_ib_setup_per_ibdev (struct smc_ib_device*) ; 
 int smc_ism_get_vlan (struct smcd_dev*,unsigned short) ; 
 int /*<<< orphan*/  smc_lgr_free_work ; 
 TYPE_3__ smc_lgr_list ; 
 int /*<<< orphan*/  smc_llc_link_clear (struct smc_link*) ; 
 int smc_llc_link_init (struct smc_link*) ; 
 int smc_wr_alloc_link_mem (struct smc_link*) ; 
 int smc_wr_create_link (struct smc_link*) ; 
 int /*<<< orphan*/  smc_wr_free_link_mem (struct smc_link*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc_lgr_create(struct smc_sock *smc, bool is_smcd,
			  struct smc_ib_device *smcibdev, u8 ibport,
			  char *peer_systemid, unsigned short vlan_id,
			  struct smcd_dev *smcismdev, u64 peer_gid)
{
	struct smc_link_group *lgr;
	struct smc_link *lnk;
	u8 rndvec[3];
	int rc = 0;
	int i;

	if (is_smcd && vlan_id) {
		rc = smc_ism_get_vlan(smcismdev, vlan_id);
		if (rc)
			goto out;
	}

	lgr = kzalloc(sizeof(*lgr), GFP_KERNEL);
	if (!lgr) {
		rc = -ENOMEM;
		goto out;
	}
	lgr->is_smcd = is_smcd;
	lgr->sync_err = 0;
	lgr->vlan_id = vlan_id;
	rwlock_init(&lgr->sndbufs_lock);
	rwlock_init(&lgr->rmbs_lock);
	rwlock_init(&lgr->conns_lock);
	for (i = 0; i < SMC_RMBE_SIZES; i++) {
		INIT_LIST_HEAD(&lgr->sndbufs[i]);
		INIT_LIST_HEAD(&lgr->rmbs[i]);
	}
	smc_lgr_list.num += SMC_LGR_NUM_INCR;
	memcpy(&lgr->id, (u8 *)&smc_lgr_list.num, SMC_LGR_ID_SIZE);
	INIT_DELAYED_WORK(&lgr->free_work, smc_lgr_free_work);
	lgr->conns_all = RB_ROOT;
	if (is_smcd) {
		/* SMC-D specific settings */
		lgr->peer_gid = peer_gid;
		lgr->smcd = smcismdev;
	} else {
		/* SMC-R specific settings */
		lgr->role = smc->listen_smc ? SMC_SERV : SMC_CLNT;
		memcpy(lgr->peer_systemid, peer_systemid, SMC_SYSTEMID_LEN);

		lnk = &lgr->lnk[SMC_SINGLE_LINK];
		/* initialize link */
		lnk->state = SMC_LNK_ACTIVATING;
		lnk->link_id = SMC_SINGLE_LINK;
		lnk->smcibdev = smcibdev;
		lnk->ibport = ibport;
		lnk->path_mtu = smcibdev->pattr[ibport - 1].active_mtu;
		if (!smcibdev->initialized)
			smc_ib_setup_per_ibdev(smcibdev);
		get_random_bytes(rndvec, sizeof(rndvec));
		lnk->psn_initial = rndvec[0] + (rndvec[1] << 8) +
			(rndvec[2] << 16);
		rc = smc_ib_determine_gid(lnk->smcibdev, lnk->ibport,
					  vlan_id, lnk->gid, &lnk->sgid_index);
		if (rc)
			goto free_lgr;
		rc = smc_llc_link_init(lnk);
		if (rc)
			goto free_lgr;
		rc = smc_wr_alloc_link_mem(lnk);
		if (rc)
			goto clear_llc_lnk;
		rc = smc_ib_create_protection_domain(lnk);
		if (rc)
			goto free_link_mem;
		rc = smc_ib_create_queue_pair(lnk);
		if (rc)
			goto dealloc_pd;
		rc = smc_wr_create_link(lnk);
		if (rc)
			goto destroy_qp;
	}
	smc->conn.lgr = lgr;
	spin_lock_bh(&smc_lgr_list.lock);
	list_add(&lgr->list, &smc_lgr_list.list);
	spin_unlock_bh(&smc_lgr_list.lock);
	return 0;

destroy_qp:
	smc_ib_destroy_queue_pair(lnk);
dealloc_pd:
	smc_ib_dealloc_protection_domain(lnk);
free_link_mem:
	smc_wr_free_link_mem(lnk);
clear_llc_lnk:
	smc_llc_link_clear(lnk);
free_lgr:
	kfree(lgr);
out:
	return rc;
}