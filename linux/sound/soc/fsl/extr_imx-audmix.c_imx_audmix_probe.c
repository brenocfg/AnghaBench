#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct snd_soc_dapm_route {int dummy; } ;
struct snd_soc_dai_link_component {char* dai_name; char* name; struct device_node* of_node; } ;
struct snd_soc_dai_link {int dummy; } ;
struct snd_soc_codec_conf {int dummy; } ;
struct TYPE_20__ {TYPE_13__* parent; struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct of_phandle_args {struct device_node* np; } ;
struct TYPE_19__ {int num_links; int num_configs; int num_dapm_routes; char* name; int /*<<< orphan*/  owner; TYPE_5__* dev; TYPE_3__* dapm_routes; TYPE_2__* codec_conf; TYPE_1__* dai_link; } ;
struct imx_audmix {int num_dai; int num_dai_conf; int num_dapm_routes; TYPE_4__ card; TYPE_3__* dapm_routes; TYPE_2__* dai_conf; TYPE_1__* dai; struct platform_device* out_pdev; struct platform_device* audmix_pdev; int /*<<< orphan*/  cpu_mclk; } ;
struct device_node {char* full_name; } ;
struct TYPE_18__ {char* source; char* sink; } ;
struct TYPE_17__ {char* name_prefix; struct device_node* of_node; } ;
struct TYPE_16__ {int num_cpus; int num_codecs; int num_platforms; char* name; char* stream_name; int dynamic; int dpcm_playback; int dpcm_capture; int ignore_pmdown_time; int no_pcm; int /*<<< orphan*/ * ops; struct snd_soc_dai_link_component* platforms; struct snd_soc_dai_link_component* cpus; struct snd_soc_dai_link_component* codecs; } ;
struct TYPE_15__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FSL_AUDMIX_MAX_DAIS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_13__*,char*,char*) ; 
 char* dev_name (TYPE_5__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_5__*,char*) ; 
 void* devm_kasprintf (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 void* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  imx_audmix_be_ops ; 
 int /*<<< orphan*/  imx_audmix_fe_ops ; 
 int of_count_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *,int,struct of_phandle_args*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_4__*) ; 
 int /*<<< orphan*/  put_device (TYPE_5__*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_4__*,struct imx_audmix*) ; 

__attribute__((used)) static int imx_audmix_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *audmix_np = NULL, *out_cpu_np = NULL;
	struct platform_device *audmix_pdev = NULL;
	struct platform_device *cpu_pdev;
	struct of_phandle_args args;
	struct imx_audmix *priv;
	int i, num_dai, ret;
	const char *fe_name_pref = "HiFi-AUDMIX-FE-";
	char *be_name, *be_pb, *be_cp, *dai_name, *capture_dai_name;

	if (pdev->dev.parent) {
		audmix_np = pdev->dev.parent->of_node;
	} else {
		dev_err(&pdev->dev, "Missing parent device.\n");
		return -EINVAL;
	}

	if (!audmix_np) {
		dev_err(&pdev->dev, "Missing DT node for parent device.\n");
		return -EINVAL;
	}

	audmix_pdev = of_find_device_by_node(audmix_np);
	if (!audmix_pdev) {
		dev_err(&pdev->dev, "Missing AUDMIX platform device for %s\n",
			np->full_name);
		return -EINVAL;
	}
	put_device(&audmix_pdev->dev);

	num_dai = of_count_phandle_with_args(audmix_np, "dais", NULL);
	if (num_dai != FSL_AUDMIX_MAX_DAIS) {
		dev_err(&pdev->dev, "Need 2 dais to be provided for %s\n",
			audmix_np->full_name);
		return -EINVAL;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->num_dai = 2 * num_dai;
	priv->dai = devm_kzalloc(&pdev->dev, priv->num_dai *
				 sizeof(struct snd_soc_dai_link), GFP_KERNEL);
	if (!priv->dai)
		return -ENOMEM;

	priv->num_dai_conf = num_dai;
	priv->dai_conf = devm_kzalloc(&pdev->dev, priv->num_dai_conf *
				      sizeof(struct snd_soc_codec_conf),
				      GFP_KERNEL);
	if (!priv->dai_conf)
		return -ENOMEM;

	priv->num_dapm_routes = 3 * num_dai;
	priv->dapm_routes = devm_kzalloc(&pdev->dev, priv->num_dapm_routes *
					 sizeof(struct snd_soc_dapm_route),
					 GFP_KERNEL);
	if (!priv->dapm_routes)
		return -ENOMEM;

	for (i = 0; i < num_dai; i++) {
		struct snd_soc_dai_link_component *dlc;

		/* for CPU/Codec/Platform x 2 */
		dlc = devm_kzalloc(&pdev->dev, 6 * sizeof(*dlc), GFP_KERNEL);
		if (!dlc) {
			dev_err(&pdev->dev, "failed to allocate dai_link\n");
			return -ENOMEM;
		}

		ret = of_parse_phandle_with_args(audmix_np, "dais", NULL, i,
						 &args);
		if (ret < 0) {
			dev_err(&pdev->dev, "of_parse_phandle_with_args failed\n");
			return ret;
		}

		cpu_pdev = of_find_device_by_node(args.np);
		if (!cpu_pdev) {
			dev_err(&pdev->dev, "failed to find SAI platform device\n");
			return -EINVAL;
		}
		put_device(&cpu_pdev->dev);

		dai_name = devm_kasprintf(&pdev->dev, GFP_KERNEL, "%s%s",
					  fe_name_pref, args.np->full_name + 1);

		dev_info(pdev->dev.parent, "DAI FE name:%s\n", dai_name);

		if (i == 0) {
			out_cpu_np = args.np;
			capture_dai_name =
				devm_kasprintf(&pdev->dev, GFP_KERNEL, "%s %s",
					       dai_name, "CPU-Capture");
		}

		priv->dai[i].cpus = &dlc[0];
		priv->dai[i].codecs = &dlc[1];
		priv->dai[i].platforms = &dlc[2];

		priv->dai[i].num_cpus = 1;
		priv->dai[i].num_codecs = 1;
		priv->dai[i].num_platforms = 1;

		priv->dai[i].name = dai_name;
		priv->dai[i].stream_name = "HiFi-AUDMIX-FE";
		priv->dai[i].codecs->dai_name = "snd-soc-dummy-dai";
		priv->dai[i].codecs->name = "snd-soc-dummy";
		priv->dai[i].cpus->of_node = args.np;
		priv->dai[i].cpus->dai_name = dev_name(&cpu_pdev->dev);
		priv->dai[i].platforms->of_node = args.np;
		priv->dai[i].dynamic = 1;
		priv->dai[i].dpcm_playback = 1;
		priv->dai[i].dpcm_capture = (i == 0 ? 1 : 0);
		priv->dai[i].ignore_pmdown_time = 1;
		priv->dai[i].ops = &imx_audmix_fe_ops;

		/* Add AUDMIX Backend */
		be_name = devm_kasprintf(&pdev->dev, GFP_KERNEL,
					 "audmix-%d", i);
		be_pb = devm_kasprintf(&pdev->dev, GFP_KERNEL,
				       "AUDMIX-Playback-%d", i);
		be_cp = devm_kasprintf(&pdev->dev, GFP_KERNEL,
				       "AUDMIX-Capture-%d", i);

		priv->dai[num_dai + i].cpus = &dlc[3];
		priv->dai[num_dai + i].codecs = &dlc[4];
		priv->dai[num_dai + i].platforms = &dlc[5];

		priv->dai[num_dai + i].num_cpus = 1;
		priv->dai[num_dai + i].num_codecs = 1;
		priv->dai[num_dai + i].num_platforms = 1;

		priv->dai[num_dai + i].name = be_name;
		priv->dai[num_dai + i].codecs->dai_name = "snd-soc-dummy-dai";
		priv->dai[num_dai + i].codecs->name = "snd-soc-dummy";
		priv->dai[num_dai + i].cpus->of_node = audmix_np;
		priv->dai[num_dai + i].cpus->dai_name = be_name;
		priv->dai[num_dai + i].platforms->name = "snd-soc-dummy";
		priv->dai[num_dai + i].no_pcm = 1;
		priv->dai[num_dai + i].dpcm_playback = 1;
		priv->dai[num_dai + i].dpcm_capture  = 1;
		priv->dai[num_dai + i].ignore_pmdown_time = 1;
		priv->dai[num_dai + i].ops = &imx_audmix_be_ops;

		priv->dai_conf[i].of_node = args.np;
		priv->dai_conf[i].name_prefix = dai_name;

		priv->dapm_routes[i].source =
			devm_kasprintf(&pdev->dev, GFP_KERNEL, "%s %s",
				       dai_name, "CPU-Playback");
		priv->dapm_routes[i].sink = be_pb;
		priv->dapm_routes[num_dai + i].source   = be_pb;
		priv->dapm_routes[num_dai + i].sink     = be_cp;
		priv->dapm_routes[2 * num_dai + i].source = be_cp;
		priv->dapm_routes[2 * num_dai + i].sink   = capture_dai_name;
	}

	cpu_pdev = of_find_device_by_node(out_cpu_np);
	if (!cpu_pdev) {
		dev_err(&pdev->dev, "failed to find SAI platform device\n");
		return -EINVAL;
	}
	put_device(&cpu_pdev->dev);

	priv->cpu_mclk = devm_clk_get(&cpu_pdev->dev, "mclk1");
	if (IS_ERR(priv->cpu_mclk)) {
		ret = PTR_ERR(priv->cpu_mclk);
		dev_err(&cpu_pdev->dev, "failed to get DAI mclk1: %d\n", ret);
		return -EINVAL;
	}

	priv->audmix_pdev = audmix_pdev;
	priv->out_pdev  = cpu_pdev;

	priv->card.dai_link = priv->dai;
	priv->card.num_links = priv->num_dai;
	priv->card.codec_conf = priv->dai_conf;
	priv->card.num_configs = priv->num_dai_conf;
	priv->card.dapm_routes = priv->dapm_routes;
	priv->card.num_dapm_routes = priv->num_dapm_routes;
	priv->card.dev = &pdev->dev;
	priv->card.owner = THIS_MODULE;
	priv->card.name = "imx-audmix";

	platform_set_drvdata(pdev, &priv->card);
	snd_soc_card_set_drvdata(&priv->card, priv);

	ret = devm_snd_soc_register_card(&pdev->dev, &priv->card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed\n");
		return ret;
	}

	return ret;
}