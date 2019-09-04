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
struct lpfc_vport {int dummy; } ;

/* Variables and functions */

inline void
lpfc_debugfs_initialize(struct lpfc_vport *vport)
{
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	struct lpfc_hba   *phba = vport->phba;
	char name[64];
	uint32_t num, i;
	bool pport_setup = false;

	if (!lpfc_debugfs_enable)
		return;

	/* Setup lpfc root directory */
	if (!lpfc_debugfs_root) {
		lpfc_debugfs_root = debugfs_create_dir("lpfc", NULL);
		atomic_set(&lpfc_debugfs_hba_count, 0);
		if (!lpfc_debugfs_root) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "0408 Cannot create debugfs root\n");
			goto debug_failed;
		}
	}
	if (!lpfc_debugfs_start_time)
		lpfc_debugfs_start_time = jiffies;

	/* Setup funcX directory for specific HBA PCI function */
	snprintf(name, sizeof(name), "fn%d", phba->brd_no);
	if (!phba->hba_debugfs_root) {
		pport_setup = true;
		phba->hba_debugfs_root =
			debugfs_create_dir(name, lpfc_debugfs_root);
		if (!phba->hba_debugfs_root) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "0412 Cannot create debugfs hba\n");
			goto debug_failed;
		}
		atomic_inc(&lpfc_debugfs_hba_count);
		atomic_set(&phba->debugfs_vport_count, 0);

		/* Setup hbqinfo */
		snprintf(name, sizeof(name), "hbqinfo");
		phba->debug_hbqinfo =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				 phba->hba_debugfs_root,
				 phba, &lpfc_debugfs_op_hbqinfo);
		if (!phba->debug_hbqinfo) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0411 Cannot create debugfs hbqinfo\n");
			goto debug_failed;
		}

		/* Setup dumpHBASlim */
		if (phba->sli_rev < LPFC_SLI_REV4) {
			snprintf(name, sizeof(name), "dumpHBASlim");
			phba->debug_dumpHBASlim =
				debugfs_create_file(name,
					S_IFREG|S_IRUGO|S_IWUSR,
					phba->hba_debugfs_root,
					phba, &lpfc_debugfs_op_dumpHBASlim);
			if (!phba->debug_dumpHBASlim) {
				lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
						 "0413 Cannot create debugfs "
						"dumpHBASlim\n");
				goto debug_failed;
			}
		} else
			phba->debug_dumpHBASlim = NULL;

		/* Setup dumpHostSlim */
		if (phba->sli_rev < LPFC_SLI_REV4) {
			snprintf(name, sizeof(name), "dumpHostSlim");
			phba->debug_dumpHostSlim =
				debugfs_create_file(name,
					S_IFREG|S_IRUGO|S_IWUSR,
					phba->hba_debugfs_root,
					phba, &lpfc_debugfs_op_dumpHostSlim);
			if (!phba->debug_dumpHostSlim) {
				lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
						 "0414 Cannot create debugfs "
						 "dumpHostSlim\n");
				goto debug_failed;
			}
		} else
			phba->debug_dumpHostSlim = NULL;

		/* Setup dumpData */
		snprintf(name, sizeof(name), "dumpData");
		phba->debug_dumpData =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				 phba->hba_debugfs_root,
				 phba, &lpfc_debugfs_op_dumpData);
		if (!phba->debug_dumpData) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0800 Cannot create debugfs dumpData\n");
			goto debug_failed;
		}

		/* Setup dumpDif */
		snprintf(name, sizeof(name), "dumpDif");
		phba->debug_dumpDif =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				 phba->hba_debugfs_root,
				 phba, &lpfc_debugfs_op_dumpDif);
		if (!phba->debug_dumpDif) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0801 Cannot create debugfs dumpDif\n");
			goto debug_failed;
		}

		/* Setup DIF Error Injections */
		snprintf(name, sizeof(name), "InjErrLBA");
		phba->debug_InjErrLBA =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_InjErrLBA) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0807 Cannot create debugfs InjErrLBA\n");
			goto debug_failed;
		}
		phba->lpfc_injerr_lba = LPFC_INJERR_LBA_OFF;

		snprintf(name, sizeof(name), "InjErrNPortID");
		phba->debug_InjErrNPortID =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_InjErrNPortID) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0809 Cannot create debugfs InjErrNPortID\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "InjErrWWPN");
		phba->debug_InjErrWWPN =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_InjErrWWPN) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0810 Cannot create debugfs InjErrWWPN\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "writeGuardInjErr");
		phba->debug_writeGuard =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_writeGuard) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0802 Cannot create debugfs writeGuard\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "writeAppInjErr");
		phba->debug_writeApp =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_writeApp) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0803 Cannot create debugfs writeApp\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "writeRefInjErr");
		phba->debug_writeRef =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_writeRef) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0804 Cannot create debugfs writeRef\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "readGuardInjErr");
		phba->debug_readGuard =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_readGuard) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0808 Cannot create debugfs readGuard\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "readAppInjErr");
		phba->debug_readApp =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_readApp) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0805 Cannot create debugfs readApp\n");
			goto debug_failed;
		}

		snprintf(name, sizeof(name), "readRefInjErr");
		phba->debug_readRef =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
			phba->hba_debugfs_root,
			phba, &lpfc_debugfs_op_dif_err);
		if (!phba->debug_readRef) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				"0806 Cannot create debugfs readApp\n");
			goto debug_failed;
		}

		/* Setup slow ring trace */
		if (lpfc_debugfs_max_slow_ring_trc) {
			num = lpfc_debugfs_max_slow_ring_trc - 1;
			if (num & lpfc_debugfs_max_slow_ring_trc) {
				/* Change to be a power of 2 */
				num = lpfc_debugfs_max_slow_ring_trc;
				i = 0;
				while (num > 1) {
					num = num >> 1;
					i++;
				}
				lpfc_debugfs_max_slow_ring_trc = (1 << i);
				pr_err("lpfc_debugfs_max_disc_trc changed to "
				       "%d\n", lpfc_debugfs_max_disc_trc);
			}
		}

		snprintf(name, sizeof(name), "slow_ring_trace");
		phba->debug_slow_ring_trc =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				 phba->hba_debugfs_root,
				 phba, &lpfc_debugfs_op_slow_ring_trc);
		if (!phba->debug_slow_ring_trc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "0415 Cannot create debugfs "
					 "slow_ring_trace\n");
			goto debug_failed;
		}
		if (!phba->slow_ring_trc) {
			phba->slow_ring_trc = kmalloc(
				(sizeof(struct lpfc_debugfs_trc) *
				lpfc_debugfs_max_slow_ring_trc),
				GFP_KERNEL);
			if (!phba->slow_ring_trc) {
				lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
						 "0416 Cannot create debugfs "
						 "slow_ring buffer\n");
				goto debug_failed;
			}
			atomic_set(&phba->slow_ring_trc_cnt, 0);
			memset(phba->slow_ring_trc, 0,
				(sizeof(struct lpfc_debugfs_trc) *
				lpfc_debugfs_max_slow_ring_trc));
		}

		snprintf(name, sizeof(name), "nvmeio_trc");
		phba->debug_nvmeio_trc =
			debugfs_create_file(name, 0644,
					    phba->hba_debugfs_root,
					    phba, &lpfc_debugfs_op_nvmeio_trc);
		if (!phba->debug_nvmeio_trc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "0574 No create debugfs nvmeio_trc\n");
			goto debug_failed;
		}

		atomic_set(&phba->nvmeio_trc_cnt, 0);
		if (lpfc_debugfs_max_nvmeio_trc) {
			num = lpfc_debugfs_max_nvmeio_trc - 1;
			if (num & lpfc_debugfs_max_disc_trc) {
				/* Change to be a power of 2 */
				num = lpfc_debugfs_max_nvmeio_trc;
				i = 0;
				while (num > 1) {
					num = num >> 1;
					i++;
				}
				lpfc_debugfs_max_nvmeio_trc = (1 << i);
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"0575 lpfc_debugfs_max_nvmeio_trc "
						"changed to %d\n",
						lpfc_debugfs_max_nvmeio_trc);
			}
			phba->nvmeio_trc_size = lpfc_debugfs_max_nvmeio_trc;

			/* Allocate trace buffer and initialize */
			phba->nvmeio_trc = kzalloc(
				(sizeof(struct lpfc_debugfs_nvmeio_trc) *
				phba->nvmeio_trc_size), GFP_KERNEL);

			if (!phba->nvmeio_trc) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"0576 Cannot create debugfs "
						"nvmeio_trc buffer\n");
				goto nvmeio_off;
			}
			phba->nvmeio_trc_on = 1;
			phba->nvmeio_trc_output_idx = 0;
			phba->nvmeio_trc = NULL;
		} else {
nvmeio_off:
			phba->nvmeio_trc_size = 0;
			phba->nvmeio_trc_on = 0;
			phba->nvmeio_trc_output_idx = 0;
			phba->nvmeio_trc = NULL;
		}
	}

	snprintf(name, sizeof(name), "vport%d", vport->vpi);
	if (!vport->vport_debugfs_root) {
		vport->vport_debugfs_root =
			debugfs_create_dir(name, phba->hba_debugfs_root);
		if (!vport->vport_debugfs_root) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "0417 Can't create debugfs\n");
			goto debug_failed;
		}
		atomic_inc(&phba->debugfs_vport_count);
	}

	if (lpfc_debugfs_max_disc_trc) {
		num = lpfc_debugfs_max_disc_trc - 1;
		if (num & lpfc_debugfs_max_disc_trc) {
			/* Change to be a power of 2 */
			num = lpfc_debugfs_max_disc_trc;
			i = 0;
			while (num > 1) {
				num = num >> 1;
				i++;
			}
			lpfc_debugfs_max_disc_trc = (1 << i);
			pr_err("lpfc_debugfs_max_disc_trc changed to %d\n",
			       lpfc_debugfs_max_disc_trc);
		}
	}

	vport->disc_trc = kzalloc(
		(sizeof(struct lpfc_debugfs_trc) * lpfc_debugfs_max_disc_trc),
		GFP_KERNEL);

	if (!vport->disc_trc) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0418 Cannot create debugfs disc trace "
				 "buffer\n");
		goto debug_failed;
	}
	atomic_set(&vport->disc_trc_cnt, 0);

	snprintf(name, sizeof(name), "discovery_trace");
	vport->debug_disc_trc =
		debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				 vport->vport_debugfs_root,
				 vport, &lpfc_debugfs_op_disc_trc);
	if (!vport->debug_disc_trc) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0419 Cannot create debugfs "
				 "discovery_trace\n");
		goto debug_failed;
	}
	snprintf(name, sizeof(name), "nodelist");
	vport->debug_nodelist =
		debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				 vport->vport_debugfs_root,
				 vport, &lpfc_debugfs_op_nodelist);
	if (!vport->debug_nodelist) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "2985 Can't create debugfs nodelist\n");
		goto debug_failed;
	}

	snprintf(name, sizeof(name), "nvmestat");
	vport->debug_nvmestat =
		debugfs_create_file(name, 0644,
				    vport->vport_debugfs_root,
				    vport, &lpfc_debugfs_op_nvmestat);
	if (!vport->debug_nvmestat) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0811 Cannot create debugfs nvmestat\n");
		goto debug_failed;
	}

	snprintf(name, sizeof(name), "nvmektime");
	vport->debug_nvmektime =
		debugfs_create_file(name, 0644,
				    vport->vport_debugfs_root,
				    vport, &lpfc_debugfs_op_nvmektime);
	if (!vport->debug_nvmektime) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0815 Cannot create debugfs nvmektime\n");
		goto debug_failed;
	}

	snprintf(name, sizeof(name), "cpucheck");
	vport->debug_cpucheck =
		debugfs_create_file(name, 0644,
				    vport->vport_debugfs_root,
				    vport, &lpfc_debugfs_op_cpucheck);
	if (!vport->debug_cpucheck) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0819 Cannot create debugfs cpucheck\n");
		goto debug_failed;
	}

	/*
	 * The following section is for additional directories/files for the
	 * physical port.
	 */

	if (!pport_setup)
		goto debug_failed;

	/*
	 * iDiag debugfs root entry points for SLI4 device only
	 */
	if (phba->sli_rev < LPFC_SLI_REV4)
		goto debug_failed;

	snprintf(name, sizeof(name), "iDiag");
	if (!phba->idiag_root) {
		phba->idiag_root =
			debugfs_create_dir(name, phba->hba_debugfs_root);
		if (!phba->idiag_root) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "2922 Can't create idiag debugfs\n");
			goto debug_failed;
		}
		/* Initialize iDiag data structure */
		memset(&idiag, 0, sizeof(idiag));
	}

	/* iDiag read PCI config space */
	snprintf(name, sizeof(name), "pciCfg");
	if (!phba->idiag_pci_cfg) {
		phba->idiag_pci_cfg =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				phba->idiag_root, phba, &lpfc_idiag_op_pciCfg);
		if (!phba->idiag_pci_cfg) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "2923 Can't create idiag debugfs\n");
			goto debug_failed;
		}
		idiag.offset.last_rd = 0;
	}

	/* iDiag PCI BAR access */
	snprintf(name, sizeof(name), "barAcc");
	if (!phba->idiag_bar_acc) {
		phba->idiag_bar_acc =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				phba->idiag_root, phba, &lpfc_idiag_op_barAcc);
		if (!phba->idiag_bar_acc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					"3056 Can't create idiag debugfs\n");
			goto debug_failed;
		}
		idiag.offset.last_rd = 0;
	}

	/* iDiag get PCI function queue information */
	snprintf(name, sizeof(name), "queInfo");
	if (!phba->idiag_que_info) {
		phba->idiag_que_info =
			debugfs_create_file(name, S_IFREG|S_IRUGO,
			phba->idiag_root, phba, &lpfc_idiag_op_queInfo);
		if (!phba->idiag_que_info) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "2924 Can't create idiag debugfs\n");
			goto debug_failed;
		}
	}

	/* iDiag access PCI function queue */
	snprintf(name, sizeof(name), "queAcc");
	if (!phba->idiag_que_acc) {
		phba->idiag_que_acc =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				phba->idiag_root, phba, &lpfc_idiag_op_queAcc);
		if (!phba->idiag_que_acc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "2926 Can't create idiag debugfs\n");
			goto debug_failed;
		}
	}

	/* iDiag access PCI function doorbell registers */
	snprintf(name, sizeof(name), "drbAcc");
	if (!phba->idiag_drb_acc) {
		phba->idiag_drb_acc =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				phba->idiag_root, phba, &lpfc_idiag_op_drbAcc);
		if (!phba->idiag_drb_acc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "2927 Can't create idiag debugfs\n");
			goto debug_failed;
		}
	}

	/* iDiag access PCI function control registers */
	snprintf(name, sizeof(name), "ctlAcc");
	if (!phba->idiag_ctl_acc) {
		phba->idiag_ctl_acc =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				phba->idiag_root, phba, &lpfc_idiag_op_ctlAcc);
		if (!phba->idiag_ctl_acc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					 "2981 Can't create idiag debugfs\n");
			goto debug_failed;
		}
	}

	/* iDiag access mbox commands */
	snprintf(name, sizeof(name), "mbxAcc");
	if (!phba->idiag_mbx_acc) {
		phba->idiag_mbx_acc =
			debugfs_create_file(name, S_IFREG|S_IRUGO|S_IWUSR,
				phba->idiag_root, phba, &lpfc_idiag_op_mbxAcc);
		if (!phba->idiag_mbx_acc) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
					"2980 Can't create idiag debugfs\n");
			goto debug_failed;
		}
	}

	/* iDiag extents access commands */
	if (phba->sli4_hba.extents_in_use) {
		snprintf(name, sizeof(name), "extAcc");
		if (!phba->idiag_ext_acc) {
			phba->idiag_ext_acc =
				debugfs_create_file(name,
						    S_IFREG|S_IRUGO|S_IWUSR,
						    phba->idiag_root, phba,
						    &lpfc_idiag_op_extAcc);
			if (!phba->idiag_ext_acc) {
				lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
						"2986 Cant create "
						"idiag debugfs\n");
				goto debug_failed;
			}
		}
	}

debug_failed:
	return;
#endif
}